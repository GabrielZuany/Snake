#ifndef _TARQUIVOS_H_
#define _TARQUIVOS_H_

#define COBRA '>'
#define COBRA_DIREITA '>'
#define COBRA_CIMA '^'
#define COBRA_BAIXO 'v'
#define COBRA_ESQUERDA '<'

//--Definição de tipo de dados--//
typedef struct {
    FILE *Resumo;
    FILE *Heatmap;
    FILE *Ranking;
    FILE *Estatisticas;
}tArquivos;


/**
 * @brief Abre o arquivo para escrita.
 * 
 * @param Caminho string com o caminho do arquivo a ser aberto.
 * @return FILE* arquivo aberto.
 */
FILE *RetornaArquivoAberto(char Caminho[]);


/**
 * @brief Abre todos os arquivos para a manipulação.
 * 
 * @param CaminhoResumo caminho relativo do resumo.txt
 * @param CaminhoEstatisticas caminho relativo das estaisticas.txt
 * @param CaminhoHeatMap caminho relativo do heatmap.txt
 * @param CaminhoRanking caminho relativo do ranking.txt
 * @return tArquivos struct com os arquivos abertos.
 */
tArquivos AbreArquivos(char CaminhoResumo[], char CaminhoEstatisticas[], char CaminhoHeatMap[], char CaminhoRanking[]);


/**
 * @brief Retorna o file heatmap.txt (evitar acesso indevido. Acesso restrito à função).
 * 
 * @param jogoArquivo struct com os arquivos.
 * @return FILE* heatmap.txt
 */
FILE *RetornaHeatMap(tArquivos jogoArquivo);


/**
 * @brief Retorna o file ranking.txt (evitar acesso indevido. Acesso restrito à função).
 * 
 * @param jogoArquivo struct com os arquivos.
 * @return FILE* ranking.txt
 */
FILE *RetornaRanking(tArquivos jogoArquivo);


/**
 * @brief Retorna o file resumo.txt (evitar acesso indevido. Acesso restrito à função).
 * 
 * @param jogoArquivo struct com os arquivos.
 * @return FILE* resumo.txt
 */
FILE *RetornaResumo(tArquivos jogoArquivo);


/**
 * @brief Retorna o file estatisticas.txt (evitar acesso indevido. Acesso restrito à função).
 * 
 * @param jogoArquivo struct com os arquivos.
 * @return FILE* estatisticas.txt
 */
FILE *RetornaEstatisticas(tArquivos jogoArquivo);

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