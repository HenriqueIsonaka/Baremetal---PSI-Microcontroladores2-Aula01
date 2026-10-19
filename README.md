Atividade threads: um led com ciclo de 1 segundo e outro com ciclo de 500ms.
---
Leds utilizados: verde e azul.

Lógica de programação: Criar um thread que altera o estado do led azul a cada 500ms e fazer com que na main o led verde tenha seu estado alterado a cada 1000ms.  Dessa forma, o ciclo de um led não altera o ciclo do outro.
----
Atividade baremetal: um led com ciclo de 1 segundo e outro com ciclo de 500ms.

Leds utilizados: verde e azul.

Lógica de programação: Configurar um delay fixo de 500ms e criar um looping na função em que esse delay ocorra duas vezes: na primeira apenas o led azul alterna de estado (liga/desliga), e na segunda ambos os leds alternam de estado.

Resultados esperados: O led da placa fica em um ciclo em que, primeiro, por 500ms ambos os leds ficam acesos (led da placa fica cor turquesa), depois, por 500ms  apenas o led verde (led da placa fica cor verde), depois, por 500ms apenas o led azul (led da placa fica cor azul), e, por fim, por 500ms ambos os leds ficam apagados. Isso ocorrerá porque a duração dos ciclos dos leds é diferente, e esses serão executados paralelamente.

Resultados obtidos: Foram coerentes com o programado.

Atividade threads (desafio): um led com ciclo de 1 segundo e outro com ciclo de 350ms.
---
Leds utilizados: verde e azul.

Lógica de programação:Criar um thread que altera o estado do led azul a cada 350ms e fazer com que na main o led verde tenha seu estado alterado a cada 1000ms.  Dessa forma, o ciclo de um led não altera o ciclo do outro.

Resultados esperados: O led da placa varia entre as cores turquesa, azul, verde e apagado, de forma que o led azul fica ligando e desligando a cada 350ms, o led verde fica ligando e desligando a cada 1 segundo e o led fica turquesa quando ambos os leds azul e verde estão ligados.

Resultados obtidos: Foram coerentes com o programado

*Obs: Percebemos que trabalhar com threads facilitou o este desafio, pois possibilitou executar os dois ciclos de leds paralelamente ao mesmo tempo.
----

Atividade baremetal (desafio): um led com ciclo de 1 segundo e outro com ciclo de 350ms.

Leds utilizados: verde e azul.

Lógica de programação: Configurar um delay de 50 ms, criar um looping que repete ele infinitamente e variáveis de inteiros “i” e “j” que armazenam valores de quantas vezes esse delay ocorre, aumentando em 1 a cada repetição, de modo a agirem como contadores . Quando i chega ao valor 7, o que indica a conclusão de um ciclo de 350ms, o led verde alterna de estado e este inteiro zera (para reiniciar a contagem), e quando j chega ao valor 20, o que indica a conclusão de um ciclo de 1000ms, o led azul alterna de estado e este inteiro também zera. Desse modo, os dois leds tem ciclos independentes de tempos diferentes, um de 350ms e outro de 1000ms.

Resultados esperados: O led da placa varia entre as cores turquesa, azul, verde e apagado, de forma que o led verde fica ligando e desligando a cada 350ms, o led azul fica ligando e desligando a cada 1 segundo e o led fica turquesa quando ambos os leds azul e verde estão ligados.

Resultados obtidos: Foram coerentes com o programado

*Obs: Um fato curioso que notamos na realização do desafio é que não foi intuitivo trabalhar com os dois leds com ciclos paralelos em uma programação baremetal, uma vez que não era possível ordenar um looping com delays como no primeiro exercício, já que os dois ciclos não tinham muitos pontos de encontro comuns. Para contornar esse problema foi necessário o estabelecimento de um sistema de contagem a partir de variáveis inteiras.


