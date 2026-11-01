
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define PRIORIDADE 5
#define TAMANHO_PILHA 1024

volatile int contador = 0;

/* Semáforos para sincronizar as threads */
K_SEM_DEFINE(sem_leitura, 0, 2);
K_SEM_DEFINE(sem_escrita, 0, 2);
K_SEM_DEFINE(sem_inicio, 0, 2);

/* Pilhas */
K_THREAD_STACK_DEFINE(pilha_1, TAMANHO_PILHA);
K_THREAD_STACK_DEFINE(pilha_2, TAMANHO_PILHA);

struct k_thread thread_1_data;
struct k_thread thread_2_data;

/* Thread 1 */
void thread_1(void *a, void *b, void *c)
{
    int valor;

    k_sem_take(&sem_inicio, K_FOREVER);

    /* Lê o valor compartilhado */
    valor = contador;

    printk("Thread 1 leu: %d\n", valor);

    /* Informa que terminou a leitura */
    k_sem_give(&sem_leitura);

    /* Aguarda autorização para escrever */
    k_sem_take(&sem_escrita, K_FOREVER);

    /* Escreve o valor incrementado */
    contador = valor + 1;

    printk("Thread 1 escreveu: %d\n", contador);
}

/* Thread 2 */
void thread_2(void *a, void *b, void *c)
{
    int valor;

    k_sem_take(&sem_inicio, K_FOREVER);

    /* Lê o valor compartilhado */
    valor = contador;

    printk("Thread 2 leu: %d\n", valor);

    /* Informa que terminou a leitura */
    k_sem_give(&sem_leitura);

    /* Aguarda autorização para escrever */
    k_sem_take(&sem_escrita, K_FOREVER);

    /* Escreve o valor incrementado */
    contador = valor +1;

    printk("Thread 2 escreveu: %d\n", contador);
}

int main(void)
{
    printk("\n=== RACE CONDITION ===\n");

    contador = 0;

    k_thread_create(
        &thread_1_data,
        pilha_1,
        K_THREAD_STACK_SIZEOF(pilha_1),
        thread_1,
        NULL, NULL, NULL,
        PRIORIDADE, 0, K_NO_WAIT
    );

    k_thread_create(
        &thread_2_data,
        pilha_2,
        K_THREAD_STACK_SIZEOF(pilha_2),
        thread_2,
        NULL, NULL, NULL,
        PRIORIDADE, 0, K_NO_WAIT
    );

    /* Libera as duas threads */
    k_sem_give(&sem_inicio);
    k_sem_give(&sem_inicio);

    /* Aguarda as duas leituras */
    k_sem_take(&sem_leitura, K_FOREVER);
    k_sem_take(&sem_leitura, K_FOREVER);

    printk("\nAmbas as threads leram o contador.\n");

    /* Libera as duas escritas */
    k_sem_give(&sem_escrita);
    k_sem_give(&sem_escrita);

    /* Aguarda o término das threads */
    k_thread_join(&thread_1_data, K_FOREVER);
    k_thread_join(&thread_2_data, K_FOREVER);

    printk("\nResultado final: %d\n", contador);
    printk("Resultado esperado: 2\n");

    return 0;
}
