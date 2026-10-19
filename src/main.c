#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

void minha_thread(void)
{
    while (1) {
        k_msleep(1000);
        gpio_pin_toggle_dt(&led0);
    }
}

// Criar a thread
K_THREAD_DEFINE(minha_thread_id, 512, minha_thread, NULL, NULL, NULL, 7, 0, 0);

void main(void)
{
     int ret0;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led0)) {
        printk("Error: LED device %s is not ready\n", led0.port->name);
        return;
    }

    // Configura o pino como saída
    ret0 = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret0 < 0) {
        printk("Error %d: failed to configure LED pin\n", ret0);
        return;
    }

    printk("LED blinking on %s pin %d\n", led0.port->name, led0.pin);

    int ret1;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led1)) {
        printk("Error: LED device %s is not ready\n", led1.port->name);
        return;
    }

    // Configura o pino como saída
    ret1 = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret1 < 0) {
        printk("Error %d: failed to configure LED pin\n", ret1);
        return;
    }

    printk("LED blinking on %s pin %d\n", led1.port->name, led1.pin);
    printk("Main iniciou\n");
    
    while (1) {
        k_msleep(350);
        gpio_pin_toggle_dt(&led1);
    }
}