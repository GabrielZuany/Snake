# Snake

## O projeto
- Realizado na disciplina de Prog.I (1o Período) da Universidade Federal do Espirito Santo (UFES).<br>
- Objetivo: Aplicar conhecimentos de modularização, criação e manipulação de tipos de dados definidos pelo usuário, lógica e manipulação de arquivos.<br>
- Extra: Organização de código por meio da separação em bilbiotecas com as funções próprias criadas para esse problema.<br>

---
 
 ## Como Funciona:
 
- Executar<br>
~~~Shell
make
make PlayMap1
make PlayMap2
make PlayMap3
~~~
<ou run_map_2.sh ou run_map_3.sh>

- Informações: 
  - O jogo deve ser executado com o terminal.
  - A cabeça da cobrinha é respresentada por setas '>', '<', '^' e 'v'.
  - O corpo da cobrinha é respresentada por 'o'.
  - A comida é respresentada por '*' e o bônus de dinheiro '$'.
  - Os túneis/portais são respresentados por '@'. Caso o usuário entre em um, sairá no outro na mesma direção com a qual entrou.
  - As paredes são respresentadas por '#'. Caso o jogador acerte a parede ou o próprio corpo ele perde o jogo.
  - Os comandos válidos são: 'w', 'a', 's', 'd'
  - Caso deseje ver as informações geradas após a última jogada no mapa, os aquivos gerados se encontram na pasta "saida", encontrada na pasta mapa_<numero_do_mapa>
  - Os Arquivos de saída são: HeatMap.txt, Ranking.txt, Resumo.txt, Inicializacao.txt e Estatisticas.txt

- Objetivo: Ganhar o máximo de pontos que conseguir.


## Estatísticas/Inicialização:
 <img src="https://github.com/GabrielZuany/Snake/blob/main/media/img1.png"/>
 <br>
 
## Ranking/Resumo:
 <img src="https://github.com/GabrielZuany/Snake/blob/main/media/img2.png"/>
 <br>
 
## Heatmap:
 <img src="https://github.com/GabrielZuany/Snake/blob/main/media/img3.png"/>

## Veja o jogo em execução:
  - [Video](https://github.com/GabrielZuany/Snake/blob/main/media/run.mp4) <br><br>

## Infomações extras:

---Autor do código: Gabriel Zuany Duarte Vargas<br>
---Data: 2022, Agosto<br>
---Versão: 1.3<br>
<br>
---Última atualização: 18/11/2022 (V 1.2 -> V 1.3)<br>
    --- 1. Substituição de arquivo run.sh por Makefile
    
=============OPERAVEL, POR ENQUANTO, APENAS NO LINUX;==============
