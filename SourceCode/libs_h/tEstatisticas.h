#ifndef _TESTATISTICAS_H_
#define _TESTATISTICAS_H_
#define COMIDA '*'
#define PONTO_COMIDA 1
#define DINHEIRO '$'
#define GANHA_DINHEIRO 10

//--Definição de tipo de dados--//
typedef struct {
    int Pontos;
    int QtdComida;
    int QtdDinheiro;
    int AumentouDinheiro;
    int AumentouCorpo;
    int QtdCorpoCobra;
    int QtdMov;
    int MovBaixo;
    int MovCima;
    int MovDireita;
    int MovEsquerda;
    int NumeroDoMovimento;
    int JaMoveuCorpo;
    char movimento;
}tEstatisticas;


/**
 * @brief Registra o último movimento dado.
 * 
 * @param estatisticas struct com as estatísticas atuais.
 * @param mov último movimento.
 * @return tEstatisticas struct com as estatísticas atualizadas após o último movimento.
 */
tEstatisticas ArmazenaMovimento(tEstatisticas estatisticas, char mov);


/**
 * @brief Verifica se a célula de destino possui algum tipo de bônus e, se tiver, atualiza as estatísticas.
 * 
 * @param estatisticas struct com as estatísticas atuais.
 * @param tipo próxima célula.
 * @return tEstatisticas  struct com as estatísticas atualizadas após o movimento.
 */
tEstatisticas AtualizaPontuacao(tEstatisticas estatisticas, char tipo);


/**
 * @brief Incrementa em 1 a quantidade de comida coletada.
 * 
 * @param estatisticas struct com as estatísticas atuais.
 * @return tEstatisticas struct com as estatísticas atualizadas após o movimento.
 */
tEstatisticas AumentaComida(tEstatisticas estatisticas);


/**
 * @brief Atualiza as estatísticas atuais de acordo com o parâmetro 'BIN' relacionado ao corpo.
 * 
 * @param estatisticas struct com as estatísticas atuais.
 * @param BIN valor "binário"(1/0) como indicativo se o corpo cresceu ou não.
 * @return tEstatisticas struct com as estatísticas atualizadas após o movimento.
 */
tEstatisticas AtualizaAumentouCorpo(tEstatisticas estatisticas, int BIN);


/**
 * @brief Atualiza as estatísticas atuais de acordo com o parâmetro 'BIN' relacionado ao dinheiro.
 * 
 * @param estatisticas struct com as estatísticas atuais.
 * @param BIN valor "binário"(1/0) como indicativo se ganhou dinheiro ou não.
 * @return tEstatisticas struct com as estatísticas atualizadas após o movimento.
 */
tEstatisticas AtualizaAumentouDinheiro(tEstatisticas estatisticas, int BIN);


/**
 * @brief Inicializa os valores das estatíticas antes do início do jogo.
 * 
 * @param estatisticas struct com valores não setados.
 * @return tEstatisticas struct com valores inicializados.
 */
tEstatisticas ResetaValores(tEstatisticas estatisticas);


/**
 * @brief Incrementa contador de movimentos de acordo com o último movimento registrado.
 * 
 * @param estatisticas struct com os valores atuais das estastísticas.
 * @param mov último movimento realizado.
 * @return tEstatisticas estatísticas atualizadas.
 */
tEstatisticas AtualizaQtdMov(tEstatisticas estatisticas, char mov);


/**
 * @brief Incrementa o número do movimento para escrever em resumo.txt.
 * 
 * @param estatisticas struct com os valores atuais das estatíticas.
 * @param var número total de movimentos registrados até o momento.
 * @return tEstatisticas estatísticas atualizadas.
 */
tEstatisticas AtualizaNumeroDoMovimento(tEstatisticas estatisticas, int var);


/**
 * @brief Informa que o corpo ja foi movientado (evita duas movimentações subsequentes).
 * 
 * @param estatisticas struct com as estatísticas atuais.
 * @param BIN valor "binário"(1/0) como indicativo se já movimentou ou não.
 * @return tEstatisticas estatísticas atualizadas.
 */
tEstatisticas AtualizaJaMoveuCorpo(tEstatisticas estatisticas, int BIN);


/**
 * @brief Retorna a quantidade atual de comida.
 * 
 * @param estatisticas estatísticas atuais.
 * @return int quantidade de comida.
 */
int RetornaQtdComida(tEstatisticas estatisticas);


/**
 * @brief Retorna a quantidade atual de dinheiro.
 * 
 * @param estatisticas estatísticas atuais.
 * @return int quantidade de dinheiro.
 */
int RetornaQtdDinheiro(tEstatisticas estatisticas);


/**
 * @brief Retorna a pontuação atual.
 * 
 * @param estatisticas estatísticas atuais.
 * @return int valor da pontuação.
 */
int RetornaPontuacao(tEstatisticas estatisticas);


/**
 * @brief Retorna tamanho do corpo.
 * 
 * @param estatisticas estatísticas atuais.
 * @return int tamanho do corpo.
 */
int RetornaQtdCorpoCobra(tEstatisticas estatisticas);


/**
 * @brief Retorna a variável interna da struct.
 * 
 * @param estatisticas estatísticas atuais.
 * @return a variável interna da struct.
 */
int RetornaAumentouCorpo(tEstatisticas estatisticas);


/**
 * @brief Retorna a variável interna da struct.
 * 
 * @param estatisticas estatísticas atuais.
 * @return a variável interna da struct.
 */
int RetornaAumentouDinheiro(tEstatisticas estatisticas);


/**
 * @brief Retorna a variável interna da struct.
 * 
 * @param estatisticas estatísticas atuais.
 * @return a variável interna da struct.
 */
int RetornaQtdMov(tEstatisticas estatisticas);


/**
 * @brief Retorna a variável interna da struct.
 * 
 * @param estatisticas estatísticas atuais.
 * @return a variável interna da struct.
 */
int RetornaMovBaixo(tEstatisticas estatisticas);


/**
 * @brief Retorna a variável interna da struct.
 * 
 * @param estatisticas estatísticas atuais.
 * @return a variável interna da struct.
 */
int RetornaMovCima(tEstatisticas estatisticas);


/**
 * @brief Retorna a variável interna da struct.
 * 
 * @param estatisticas estatísticas atuais.
 * @return a variável interna da struct.
 */
int RetornaMovEsquerda(tEstatisticas estatisticas);


/**
 * @brief Retorna a variável interna da struct.
 * 
 * @param estatisticas estatísticas atuais.
 * @return a variável interna da struct.
 */
int RetornaMovDireita(tEstatisticas estatisticas);


/**
 * @brief Retorna a variável interna da struct.
 * 
 * @param estatisticas estatísticas atuais.
 * @return a variável interna da struct.
 */
int RetornaNumeroDoMovimento(tEstatisticas estatisticas);


/**
 * @brief Retorna a variável interna da struct.
 * 
 * @param estatisticas estatísticas atuais.
 * @return a variável interna da struct.
 */
int RetornaJaMoveuCorpo(tEstatisticas estatisticas);


/**
 * @brief Retorna a variável interna da struct.
 * 
 * @param estatisticas estatísticas atuais.
 * @return a variável interna da struct.
 */
char RetornaMovimento(tEstatisticas estatistica);

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