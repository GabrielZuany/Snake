/**
 * @file main.c
 * @author Gabriel Zuany Duarte Vargas (https://github.com/GabrielZuany)
 * @brief Snake Game
 * @version 1.2
 * @date 2022-10-10 (last update)
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs_h/tMainSnake.h" //Trabalha com tudo relacionado ao tJogo e ao jogo em si.

int main(int argc, char **argv){
    tJogo JOGO;
    char nomeDiretorio[1000]; // nome do diretorio
    FILE *Diretorio = NULL;
    char CaminhoResumo[1000] ,CaminhoEstatisticas[1000], CaminhoHeatMap[1000], CaminhoRanking[1000];

    //converte o vetor de caracteres em string para usar a biblioteca string.h
    CaminhoResumo[0] = '\0';
    CaminhoEstatisticas[0] = '\0';
    CaminhoHeatMap[0] = '\0';
    CaminhoRanking[0] = '\0';

    Diretorio = fopen(argv[1], "r"); //abre o caminho do diretorio digitado no terminal.
    if (Diretorio == NULL) {
        printf("ERRO: Diretorio de arquivos de configuracao nao foi informado\n");
        return 1;
    }
    sprintf(nomeDiretorio, "%s", argv[1]); //converte o nome do arquivo para string.

    //concatena o nome do diretorio com o do arquivo de saida.
    strcat(CaminhoResumo, nomeDiretorio); 
    strcat(CaminhoResumo, "/saida/resumo.txt");
    strcat(CaminhoEstatisticas, nomeDiretorio);
    strcat(CaminhoEstatisticas, "/saida/estatisticas.txt");
    strcat(CaminhoHeatMap, nomeDiretorio);
    strcat(CaminhoHeatMap, "/saida/heatmap.txt");
    strcat(CaminhoRanking, nomeDiretorio);
    strcat(CaminhoRanking, "/saida/ranking.txt");

    //Abre os arquivos de saida para escrita.
    JOGO.Arquivos = AbreArquivos(CaminhoResumo, CaminhoEstatisticas, CaminhoHeatMap, CaminhoRanking);
    JOGO = LeMapa(nomeDiretorio, JOGO);
    JOGO = InicializaValores(JOGO);
    JOGO = RealizaJogada(JOGO);
    ImprimeEstatisticas(JOGO);
    ImprimeHeatMap(JOGO);
    return 0;
}

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