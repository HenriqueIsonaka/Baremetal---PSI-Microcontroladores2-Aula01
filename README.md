Nome : Henrique Makoto Isonaka
NUSP: 17972455

Link github (Esta atividade está no branch RaceCondition): https://github.com/HenriqueIsonaka/Baremetal---PSI-Microcontroladores2-Aula01/tree/RaceCondition 

- IA utilizada: Chat GPT

- Primeiro prompt utilizado: Crie um código para o Zephyr RTOS, com utilização do microcontrolador frdm_kl25z que expõe o problema de sincronismo de utilização de recursos compartilhados que leva a condição de corrida (Race condition) - Não resultou em um código que exemplifica uma Race Condition.

- Segundo prompt utilizado: O resultado do printk não resulta em race condition  - Sucesso: resultou em um código que gera uma condição de race condition

- Descrição do código realizado: O código cria uma variável global (chamada de “contador”) e duas threads de mesma prioridade. Estas duas threads têm a função de ler o valor do contador e atribuí-lo em uma variável, imprimir esse valor,  e atribuir esse valor somado a um ao contador. Em resumo, ambas seriam visadas para somar +1 ao valor do contador. Essas threads estão sincronizadas por um semáforo que força elas a serem executadas ao mesmo tempo. Por fim, o código imprime o valor final atribuído à variável global e o seu valor esperado, que é 2, pelo fato de ambas as threads terem sido executadas uma vez.

# Resultados: 
O resultado final no “Serial Monitor” é diferente do resultado esperado, já que, como ambas as threads foram executadas uma vez, e cada uma soma 1 ao contador, o resultado deveria ser 2. Isso indica uma ocorrência de Race Condition, já que o mesmo recurso, a variável global “contador”, foi utilizada ao mesmo tempo pelas duas threads e acabou não sendo atualizada durante a execução simultânea das duas. Assim, apesar de o contador ter passado por dois processos, é como se um deles tivesse anulado ou sobrescrito o outro, o que fez com que o valor final dele fosse 1.

- Como isso poderia afetar um projeto: Isso poderia ser um problema em um projeto de larga escala porque geraria uma dessincronização entre os recursos utilizados (como variáveis globais) e as threads executadas, gerando perda de informações entre as tarefas.
