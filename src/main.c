#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>

// --- Configuração de LEDs via DeviceTree ---
#define LED_A_NODE DT_ALIAS(led0)  // LED verde
#define LED_B_NODE DT_ALIAS(led2)  // LED vermelho
#define LED_C_NODE DT_ALIAS(led1)
#define BUTTON_NODE DT_NODELABEL(user_button_0)

LOG_MODULE_REGISTER(megabrain, LOG_LEVEL_DBG); 

static const struct gpio_dt_spec ledc = GPIO_DT_SPEC_GET(LED_C_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);
static struct gpio_callback button_cb_data;

static const struct gpio_dt_spec ledA = GPIO_DT_SPEC_GET(LED_A_NODE, gpios);
static const struct gpio_dt_spec ledB = GPIO_DT_SPEC_GET(LED_B_NODE, gpios);

// --- Prioridades e tempos ---
#define PRIO_THREAD_A 5   // Maior prioridade (número menor)
#define PRIO_THREAD_B 7  // Menor prioridade
#define TEMPO_A_MS   1500   // Thread A dorme
#define TEMPO_B_MS   1000   // Thread B dorme

// ----------------------------------------------------
// THREAD A — Tarefa curta, alta prioridade
// ----------------------------------------------------

void button_isr(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    LOG_INF("Início da interrupção em %llu ms\n", k_uptime_get());
    gpio_pin_toggle_dt(&ledc);
    for (volatile int i = 0; i < 10000000; i++) {
        if (i % 100000 == 0) {
                // Aqui não imprimimos nada — apenas ocupamos a CPU
        }
    }
    LOG_INF("Fim da interrupção em %llu ms\n", k_uptime_get());
}


void thread_A(void *p1, void *p2, void *p3)
{
    uint64_t startA_ms, endA_ms;
    while (1) {
        startA_ms = k_uptime_get();

        gpio_pin_set_dt(&ledA, 1);  // Liga LED verde
        LOG_DBG("LED verde ligou em %llu ms\n", k_uptime_get());

        // Simula processamento rápido 
        for (volatile int i = 0; i < 200000; i++) {}

        LOG_DBG("Processamento rápido finalizado em %llu ms", k_uptime_get());

        gpio_pin_set_dt(&ledA, 0);  // Desliga LED verde
        endA_ms = k_uptime_get();

        LOG_INF("InicioA: %llu ms; FimA: %llu ms;  DiferençaA: %llu ms \n", startA_ms, endA_ms, endA_ms-startA_ms);
        k_msleep(TEMPO_A_MS);       // Dorme — libera CPU


    }
}

// ----------------------------------------------------
// THREAD B — Tarefa longa, baixa prioridade
// ----------------------------------------------------
void thread_B(void *p1, void *p2, void *p3)
{
    uint64_t startB_ms, endB_ms;
    while (1) {
        startB_ms = k_uptime_get();

        gpio_pin_set_dt(&ledB, 1);  // Liga LED vermelho
        LOG_DBG("LED vermelho ligou em %llu\n ms", k_uptime_get());

        // Simula processamento mais longo 
        for (volatile int i = 0; i < 10000000; i++) {
            if (i % 100000 == 0) {
                // Aqui não imprimimos nada — apenas ocupamos a CPU
            }
        }
        LOG_DBG("Processamento lento finalizado em %llu ms", k_uptime_get());

        gpio_pin_set_dt(&ledB, 0);  // Desliga LED vermelho
        endB_ms = k_uptime_get();
        LOG_INF("InicioB: %llu ms; FimB: %llu ms;  DiferençaB: %llu ms\n", startB_ms, endB_ms, endB_ms - startB_ms);
        k_msleep(TEMPO_B_MS);       // Dorme um pouco
    }
}

// ----------------------------------------------------
// Definição das threads
// ----------------------------------------------------
K_THREAD_DEFINE(a_tid, 512, thread_A, NULL, NULL, NULL,
                PRIO_THREAD_A, 0, 0);
K_THREAD_DEFINE(b_tid, 512, thread_B, NULL, NULL, NULL,
                PRIO_THREAD_B, 0, 0);

// ----------------------------------------------------
// Função principal
// ----------------------------------------------------
void main(void)
{
    int retA, retB, retc, retbutao;
    // Inicializa GPIOs dos LEDs
    if (!device_is_ready(ledA.port)) {
        LOG_ERR("ERRO: led verde não está pronto");
        return;
    }
        if (!device_is_ready(ledB.port)) {
        LOG_ERR("ERRO: led vermelho não está pronto");
        return;
    }
    if (!device_is_ready(ledc.port)) {
        LOG_ERR("ERRO: led azul não está pronto");
        return;
    }
    if (!gpio_is_ready_dt(&button)) {
        LOG_ERR("ERRO: Botão não está disponível!\n");
        return;
    }

    retA = gpio_pin_configure_dt(&ledA, GPIO_OUTPUT_INACTIVE);
    if (retA < 0) {
        LOG_ERR("Error %d: failed to configure LED pin\n", retA);
        return;
    }
    
    retB = gpio_pin_configure_dt(&ledB, GPIO_OUTPUT_INACTIVE);
    if (retB < 0) {
        LOG_ERR("Error %d: failed to configure LED pin\n", retB);
        return;
    }



    LOG_INF("=== Demonstração de Preempção com LEDs ===\n");
    LOG_INF("Thread A (vermelho): prioridade %d\n", PRIO_THREAD_A);
    LOG_INF("Thread B (verde): prioridade %d\n", PRIO_THREAD_B);

// Configurar LED e botão com pull-up

    
    
    retc = gpio_pin_configure_dt(&ledc, GPIO_OUTPUT_INACTIVE);
    if (retc < 0) {
        LOG_ERR("Error %d: failed to configure LED pin\n", retc);
        return;
    }
    
    retbutao = gpio_pin_configure_dt(&button, GPIO_INPUT | GPIO_PULL_UP);
    if (retbutao < 0) {
        LOG_ERR("Error %d: failed to configure LED pin\n", retbutao);
        return;
    }
    // Configurar interrupção na borda de descida
    gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_FALLING);
    gpio_init_callback(&button_cb_data, button_isr, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data);
    
    while (1) {
        k_sleep(K_FOREVER); // Main dorme para liberar CPU.
    }
}