#ifndef _TPOSICOES_H_
#define _TPOSICOES_H_

//--Definição de tipo de dados--//
typedef struct{
    int PosicaoCobraAntesMovimentoLinha;
    int PosicaoCobraAntesMovimentoColuna;
    int PosicaoAtualCobraLinha;
    int PosicaoAtualCobraColuna;
    int UltimaPosicaoLinhaCorpo;
    int UltimaPosicaoColunaCorpo;
}tCobra;


/**
 * @brief Armazena as coordenadas atuais da cobra de acordo com os parâmetros dados.
 * 
 * @param JogoCobra struct com as variáveis a serem atualizadas.
 * @param linha linha antes de  movimentar.
 * @param coluna coluna antes de movimentar.
 * @return tCobra struct com as variáveis de coordenada atualizadas.
 */
tCobra AtualizaPosicaoCobraAntesMovimento(tCobra JogoCobra, int linha, int coluna);


/**
 * @brief Atualiza as coordenadas da cobra de acordo com os parâmetros dados.
 * 
 * @param JogoCobra struct com as variáveis a serem atualizadas.
 * @param linha linha atual.
 * @param coluna coluna atual.
 * @return tCobra struct com as variáveis de coordenada atualizadas.
 */
tCobra AtualizaCoordenadaAtualCobra(tCobra JogoCobra, int linha, int coluna);


/**
 * @brief Atualiza as coordenadas do corpo de acordo com os parâmetros dados.
 * 
 * @param JogoCobra struct com as variáveis a serem atualizadas.
 * @param linha linha do último corpo.
 * @param coluna coluna  do último corpo.
 * @return tCobra struct com as variáveis de coordenada atualizadas.
 */
tCobra AtualizaUltimoCorpo(tCobra JogoCobra, int linha, int coluna);


/**
 * @brief Retorna a última posição registrada da cobra.
 * 
 * @param JogoCobra Struc com as variáveis registradas.
 * @param id 'L' para retornar a linha ou '<qualquer>' para retornar a coluna.
 * @return int valor da linha ou coluna.
 */
int RetornaPosicaoCobraAntesMovimento(tCobra JogoCobra, char id);


/**
 * @brief Retorna a posição atual registrada da cobra.
 * 
 * @param JogoCobra Struc com as variáveis registradas.
 * @param id 'L' para retornar a linha ou '<qualquer>' para retornar a coluna.
 * @return int valor da linha ou coluna.
 */
int RetornaPosicaoAtualCobra(tCobra JogoCobra, char id);


/**
 * @brief Retorna a última posição registrada do corpo.
 * 
 * @param JogoCobra Struc com as variáveis registradas.
 * @param tipo 'L' para retornar a linha ou '<qualquer>' para retornar a coluna.
 * @return int valor da linha ou coluna.
 */
int RetornaUltimoCorpo(tCobra JogoCobra, char tipo);

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