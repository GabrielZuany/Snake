#ifndef _TMAINSNAKE_H_
#define _TMAINSNAKE_H_
#include <stdio.h>
#include "tArquivos.h"
#include "tPosicoes.h"
#include "tEstatisticas.h"
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#define TAM_MAX_COBRA 100
#define MORREU 'X'
#define PAREDE '#'
#define ESPACO_LIVRE ' '
#define PORTAL '@'
#define CORPO 'o'
#define MOV_HORARIO 'h'
#define MOV_ANTIHORARIO 'a'
#define MOV_CONTINUA 'c'
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

//--Definição de tipo de dados--//
typedef struct{
    tCobra Cobra;
    tArquivos Arquivos;
    tEstatisticas Estatisticas;
    //--MAPEAMENTO DO CORPO--//
    int CoordenadaLinhaCorpo[100];
    int CoordenadaColunaCorpo[100];
    int ContadorCorpo;
    //--REFERENTE AO MAPA--//
    int TamanhoLinha;
    int TamanhoColuna;
    char tabuleiro[100][100];
    int TemPortal;
    int portalLinha[2];
    int portalColuna[2];
    int HeatMap[100][100];
    int velocidade;
    char movAnterior;
}tJogo;


/**
 * @brief Lê o mapa.txt para realizar o jogo.
 * 
 * @param nomeDiretorio diretório aonde se encontra o mapa.
 * @param jogo struct para registrar o mapa.
 * @return tJogo struct atualizada.
 */
tJogo LeMapa(char nomeDiretorio[], tJogo jogo);


/**
 * @brief Faz a leitura e verificação do movimento (inclusive se houve entrada da stdin ou não).
 * 
 * @param jogo struct com as informações atuais.
 * @return tJogo struct com as informações atualizadas.
 */
tJogo LeMovimentos(tJogo jogo);


/**
 * @brief Verifica se alguma tecla foi pressionada.
 * 
 * @return int a resposta se houve ou não entrada via stdin.
 */
int kbhit();


/**
 * @brief Pausa a execução por X tempo.
 * 
 * @param tempo tempo(ms).
 */
void Sleep(int tempo);


/**
 * @brief Verifica se o movimento digitado é contrário.
 * 
 * @param direcao char direção dada.
 * @param direcaoAnterio char último movimento registrado.
 * 
 * @return retorna 1 para movimento contrário ou 0 para movimento não contrário.
 */
int EhMovimentoContrario(char direcao, char direcaoAnterior)


/**
 * @brief Verifica a posição inicial da cobra. (usado para inicialização.txt)
 * 
 * @param jogo valores atuais da struct.
 * @return tJogo struct com posição atual da cobra atualizada.
 */
tJogo PosicaoInicial(tJogo jogo);


/**
 * @brief Inicializa valores da struct.
 * 
 * @param jogo struct não iinicializada.
 * @return tJogo struct atualizada.
 */
tJogo InicializaValores(tJogo jogo);


/**
 * @brief Responsável pela lógica principal de realização das jogadas.
 * 
 * @param jogo struct com as variáveis a serem trabalhadas.
 * @return tJogo struct com as informaçãoes finais.
 */
tJogo RealizaJogada(tJogo jogo);


/**
 * @brief Transporta a cobra para o outro lado do mapa caso não haja parede na borda atual.
 * 
 * @param mov movimento em curso para identificar em qual parte ela reaparecerá.
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo TeletransportaCobrinha(char mov, tJogo jogo);


/**
 * @brief Verifica próxima célula para saber se vai teleportar ou não;
 * 
 * @param jogo struct com os valores atuais.
 * @param linha próxima célula.
 * @param coluna próxima célula.
 * @param mov movimento corrente.
 * @return int 1 caso vá teleportar ou 0 caso não.
 */
int VaiTeleportarCobra(tJogo jogo, int linha, int coluna, char mov);


/**
 * @brief Verifica a célula de saída do outro portal.
 * 
 * @param jogo struct com os valores atuais.
 * @param linha linha de saída.
 * @param coluna coluna de saída.
 * @param n portal de saída.
 * @param mov movimeto corrente.
 * @return tJogo struct com os valores atualizados.
 */
tJogo VerificaCondicoesAntesMovPeloPortal(tJogo jogo, int linha, int coluna, int n, char mov);


/**
 * @brief Movimenta a cobra pelo mapa.
 * 
 * @param jogo struct com os valores atuais.
 * @param linha linha de destino.
 * @param coluna coluna de destino.
 * @param mov movimento dado.
 * @return tJogo struct com os valores atualizados.
 */
tJogo MOVIMENTA_COBRINHA(tJogo jogo, int linha, int coluna, char mov);


/**
 * @brief Quando encontrar um portal, fazer a cobra reaparecer no outro.
 * 
 * @param linha linha do portal de entrada.
 * @param coluna coluna do portal de entrada.
 * @param mov movimento corrente.
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo UsaPortal(int linha, int coluna, char mov, tJogo jogo);


/**
 * @brief Coloca a cabeça da cobra no outro portal (função interna).
 * 
 * @param jogo struct com os valores atuais.
 * @param linhaDestino linha de destino.
 * @param colunaDestino coluna de destino.
 * @param mov movimento dado.
 * @return tJogo struct com os valores atualizados.
 */
tJogo MovePeloPortal(tJogo jogo, int linhaDestino, int colunaDestino, char mov);


/**
 * @brief Verifica se há bônus para atualizar informações ou aumentar a velocidade.
 * 
 * @param linha linha da próxima célula.
 * @param coluna coluna da próxima célula.
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados. 
 */
tJogo TipoDeBonus(int linha, int coluna, tJogo jogo);


/**
 * @brief Atualiza as coordenadas da cobra.
 * 
 * @param jogo struct com os valores atuais.
 * @param mov movimento corrente.
 * @return tJogo struct com os valores atualizados.
 */
tJogo AtualizaPosicaoCobra(tJogo jogo, char mov);


/**
 * @brief Realiza movimento.
 * 
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo MoveParaCima(tJogo jogo);


/**
 * @brief Realiza movimento.
 * 
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo MoveParaBaixo(tJogo jogo);


/**
 * @brief Realiza movimento.
 * 
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo MoveParaDireita(tJogo jogo);


/**
 * @brief Realiza movimento.
 * 
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo MoveParaEsquerda(tJogo jogo);


/**
 * @brief Movimenta corpo.
 * 
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo MoveCorpo(tJogo jogo);


/**
 * @brief Movimenta o corpo.
 * 
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo AtualizaCoordenadasCorpo(tJogo jogo);


/**
 * @brief Atualiza quantidade de dinheiro.
 * 
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo AtualizaDinheiro(tJogo jogo);


/**
 * @brief Atualiza quantidade de comida.
 * 
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo AtualizaComida(tJogo jogo);


/**
 * @brief Gera uma matriz de mesmas dimensões do mapa registrando as posições que a cobra passou.
 * 
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo GeraHeatMap(tJogo jogo);


/**
 * @brief Gera comida em posições aleatórias do mapa toda vez que a cobra cresce.
 * 
 * @param jogo struct com os valores atuais.
 * @return tJogo struct com os valores atualizados.
 */
tJogo ColocaComida(tJogo jogo);


/**
 * @brief Imporime o jogo atualizado na tela.
 * 
 * @param jogo struct com os valores atuais.
 */
void ImprimeJogo(tJogo jogo);


/**
 * @brief Coloca X em todo o corpo da cobra e encaminha programa para o encerramento do jogo e fechamento de arquivos.
 * 
 * @param jogo struct com os valores atuais.
 */
void MataCobrinha(tJogo jogo);


/**
 * @brief Encerra o jogo com vitória ou derrota fechando e escrevendo em arquivos.
 * 
 * @param validador 0 para derrota, 1 para vitória.
 * @param jogo struct com os valores atuais.
 */
void EncerraJogo(int validador, tJogo jogo);


/**
 * @brief Escreve no arquivo sempre que come comida ou dinheiro (ou quando encerra o jogo).
 * 
 * @param AumentouDinheiro int que diz se aumentou dinheiro.
 * @param AumentouCorpo int que diz se aumentou corpo.
 * @param jogo struct com os valores atuais.
 */
void GeraResumo(int AumentouDinheiro, int AumentouCorpo, tJogo jogo);


/**
 * @brief Escreve as estatísticas gravadas no arquivo eststisticas.txt.
 * 
 * @param jogo struct com os valores registrados.
 */
void ImprimeEstatisticas(tJogo jogo);


/**
 * @brief Escreve as informações gravadas no arquivo heatmap.txt.
 * 
 * @param jogo struct com os valores registrados.
 */
void ImprimeHeatMap(tJogo jogo);


/**
 * @brief Escreve as posições mais visitadas ordenadamente no arquivo ranking.txt.
 * 
 * @param jogo struct com os valores registrados.
 */
void GeraRanking(tJogo jogo);


/**
 * @brief Verifica se a próxima célula é portal.
 * 
 * @param linha linha da próxima célula.
 * @param coluna coluna da próxima célula.
 * @param jogo struct com as informações atuais.
 * @return int 1 se for protal ou 0 se não for.
 */
int EhPortal(int linha , int coluna, tJogo jogo);


/**
 * @brief Varre o mapa retornando o número do portal.
 * 
 * @param linha linha do portal.
 * @param coluna coluna do portal
 * @param jogo struct com os valores atuais.
 * @return int 0 se for o primeiro, 1 se for o segundo, -1 se não form nenhum dos dois.
 */
int EncontraPosPortal(int linha, int coluna, tJogo jogo);


/**
 * @brief Verifica se a próxima célula é valida  (não é corpo nem parede).
 * 
 * @param linha linha da próxima célula.
 * @param coluna coluna da próxima célula.
 * @param jogo struct com os valores atuais.
 * @return int 1 se for válida, 0 se for inválida.
 */
int EhPosicaoValida(int linha, int coluna, tJogo jogo);


/**
 * @brief Verifica se a próxima célula é borda.
 * 
 * @param linha linha da próxima célula.
 * @param coluna coluna da próxima célula.
 * @param jogo struct com os valores atuais.
 * @return int 1 se for, 0 se não for.
 */
int EhBorda(int linha, int coluna, tJogo jogo);


/**
 * @brief Retorna um valor que correspode ao bônus encontrados.
 * 
 * @param linha linha da próxima célula.
 * @param coluna coluna da próxima célula.
 * @param jogo struct com os valores atuais.
 * @return int 1 para dinheiro, 2 para comida, 0 para nenhum.
 */
int VerificaBonus(int linha, int coluna, tJogo jogo);


/**
 * @brief Verifica se a célula é o útimo corpo (se for, move o corpo depois a cabeça).
 * 
 * @param linha linha da próxima célula.
 * @param coluna coluna da próxima célula.
 * @param jogo struct com os valores atuais.
 * @return int 1 se for, 0 se não for.
 */
int EhUltimoCorpo(int linha, int coluna, tJogo jogo);


#endif

/*
Created by: Gabriel Zuany Duarte Vargas.
Date: 10/10/2022 (Last update).
Protected by GNU V3.0.

Copyright (C) <2022>  <Gabriel Zuany Duarte Varga>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.   
*/