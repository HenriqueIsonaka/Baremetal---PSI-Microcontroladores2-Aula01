# Commit: Atividade Prioridades: Exemplo inicial
- Exemplo inicial fornecido com medidas dos tempos de início, fim e duração dos threads e printks para analizá-los no serial monitor.

- prioridades: A>B 

- tempos: A-1500ms; B-1000ms;

- Como a thread A tem prioridade maior do que a thread B, ela executa toda vez que fica pronta, ou seja, seu k_msleep acaba. Assim, ela sempre será executada a cada 1505 ms (aproximadamente) e em 50 ms. Enquanto isso, a thread B é executada toda vez que seu k_msleep finaliza e a thread A não está sendo executada. Dessa forma, muitas vezes ela é interrompida pela thread A, o que  aumenta o seu tempo entre iniciar e terminar sua execução.

# Commit: Atividade Prioridades: B com maior prioridade do que A
- Código anterior só que invertendo as prioridades.

- prioridades: B>A

- tempos: A-1500ms; B-1000ms;

- Como a thread B tem maior prioridade do que a thread A, ela tem um tempo constante entre iniciar sua execução e finalizá-la. Enquanto isso, a thread A executa toda vez que a thread B não está sendo executada. Devido ao fato de o tempo de execução da thread B ser muito alto, a thread A é executada muito menos vezes do que no caso anterior, e seu tempo entre execuções também é muito maior. Também é notável que pelo fato de o tempo de execução da thread A ser muito curto, dificilmente ela será interrompida para execução do thread B, sendo isso dependente dos tempos entre as execuções.

# Commit: Atividade Prioridades: A e B com mesma prioridade
- Código anterior só que fazendo com que a thread A e a thread B tenham prioridades iguais. Corresponde também a segunda pergunta do exercício 2.

- prioridades: A=B

- tempos: A-1500ms; B-1000ms;

- No caso em que as duas threads tem mesma prioridade, a execução entre elas ocorre de forma alternada, de modo a parecer que elas estão rodando simultaneamente. Isso faz com que o tempo entre o início e o fim da execução delas aumente no período em que estão se alternando. Por exemplo, o tempo de execução de A nestes casos subiu para 90 ms.

# Commit: Atividade Prioridades: A com prioridade maior do que B e tempos iguais
- Código igual ao primeiro código só que os tempos de A e B são iguais a 1000ms.

- prioridades: A>B

- tempos: A-1000ms; B-1000ms;

- Diminuindo o tempo de A e mantendo as prioridades do primeiro caso, foi possível observar que o número de vezes que a thread A interrompeu a execução da thread B aumentou, o que aumentou o tempo entre o início e fim da execução da thread B.

# Commit: Atividade Prioridades: B com prioridade maior do que A e A com tempo um pouco menor do que B
- Código igual ao código do segundo commit mas com A com tempo de 940ms.

- prioridades: B>A

- tempos: A-940ms; B-1000ms;

- Neste caso, em que a prioridade de A é menor do que a de B, o tempo entre as execuções de A foi manipulado de forma que ficasse um pouco menor do que o tempo de B. Assim foi possível fazer uma situação em que a execução de A pudesse ser interrompida pela execução de B, fazendo com que seu tempo entre o início e o fim da execução aumentasse muito nesses casos (de 50ms para quase 3000 ms).

# Commit: Atividade Prioridades: Removendo k_msleep da thread de maior prioridade (A)
- Código igual ao primeiro código só que comentando o k_msleep da thread A

- prioridades: A>B

- tempos: A-0; B-1000ms;

- Neste caso a thread A não parou de executar em nenhum momento, o que fez com que a thread B não conseguisse ser executada. Visualmente isso significou que o LED ficou verde o tempo todo, nunca chegando a ficar vermelho.

# Commit: Atividade Prioridades: Removendo k_msleep da thread de menor prioridade (B)
- Código igual ao primeiro código só que comentando o k_msleep da thread A

- prioridades: A>B

- tempos: A-1500ms; B-0;

- Neste caso a thread B executava em todo momento que a thread A parava de executar. Visualmente isso significou que o LED ficou aceso o tempo todo, ficando vermelho todo tempo que não estava verde.

# Commit: Atividade Prioridades: Substituindo printk por Logging e adicionando tempos intermediários para depuração
- Código igual ao primeiro código só que trocando printk por LOG_INF e adicionando LOG_DBG para depuração

- prioridades: A>B

- tempos: A-1500ms; B-1000ms;

- Foi notável uma diminuição do tempo entre as execuções da threads. Agora ele está quase sempre igual ao tempo programado(1500ms para A e 1000ms para B), sendo o início da execução da primeira thread em 0ms (antes estava em 13ms). 

# Commit: Atividade Prioridades: Botão com interrupção

- Código igual ao primeiro código só que adicionando uma interrupção de hardware a partir do botão 0 da placa (PTA16). Essa interrupção fazia com que o LED azul da placa freedom mudasse de estado e fosse rodada a mesma simulação de processamento lenta do thread B.

- prioridades: A>B

- tempos: A-1500ms; B-1000ms;

- A função da interrupção de hardware executava toda vez que o botão era apertado. Ela interrompia todas as outras threads que estavam sendo executadas, sendo que essas só eram finalizadas após sua execução terminar.

# Commit: Atividade Prioridades: Uso de logging e avisos de erro

- Código igual ao código anterior só que adicionando o uso de logging e avisos de erro (LOG_ERR) para a verificação e configuração dos pinos utilizados.

- prioridades: A>B

- tempos: A-1500ms; B-1000ms;

- Foi possível observar os benefícios do uso de logging nessa atualização do código. Não foi possível observar os avisos de erro porque o microcontrolador não falhou.

