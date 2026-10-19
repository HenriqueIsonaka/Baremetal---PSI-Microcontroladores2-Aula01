Atividade threads: um led com ciclo de 1 segundo e outro com ciclo de 500ms.
---
Leds utilizados: verde e azul.

Lógica de programação: Criar um thread que altera o estado do led azul a cada 500ms e fazer com que na main o led verde tenha seu estado alterado a cada 1000ms.  Dessa forma, o ciclo de um led não altera o ciclo do outro.

Resultados esperados: O led da placa fica em um ciclo em que, primeiro, por 500ms ambos os leds ficam acesos (led da placa fica cor turquesa), depois, por 500ms  apenas o led verde (led da placa fica cor verde), depois, por 500ms apenas o led azul (led da placa fica cor azul), e, por fim, por 500ms ambos os leds ficam apagados. Isso ocorrerá porque a duração dos ciclos dos leds é diferente, e esses serão executados paralelamente.

Resultados obtidos: Foram coerentes com o programado.

Atividade threads (desafio): um led com ciclo de 1 segundo e outro com ciclo de 350ms.
---
Leds utilizados: verde e azul.

Lógica de programação:Criar um thread que altera o estado do led azul a cada 350ms e fazer com que na main o led verde tenha seu estado alterado a cada 1000ms.  Dessa forma, o ciclo de um led não altera o ciclo do outro.

Resultados esperados: O led da placa varia entre as cores turquesa, azul, verde e apagado, de forma que o led azul fica ligando e desligando a cada 350ms, o led verde fica ligando e desligando a cada 1 segundo e o led fica turquesa quando ambos os leds azul e verde estão ligados.

Resultados obtidos: Foram coerentes com o programado

*Obs: Percebemos que trabalhar com threads facilitou o este desafio, pois possibilitou executar os dois ciclos de leds paralelamente ao mesmo tempo.
