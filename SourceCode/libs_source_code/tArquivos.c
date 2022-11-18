#include <stdio.h>
#include "../libs_h/tArquivos.h"

tArquivos AbreArquivos(char CaminhoResumo[], char CaminhoEstatisticas[], char CaminhoHeatMap[], char CaminhoRanking[]){
    tArquivos Arquivos;
    Arquivos.Resumo = RetornaArquivoAberto(CaminhoResumo);
    Arquivos.Estatisticas = RetornaArquivoAberto(CaminhoEstatisticas);
    Arquivos.Heatmap = RetornaArquivoAberto(CaminhoHeatMap);
    Arquivos.Ranking = RetornaArquivoAberto(CaminhoRanking);
    return Arquivos;
}

FILE *RetornaArquivoAberto(char Caminho[]){
    //Recebe o caminho do arquivo e retorna o arquivo aberto.
    FILE *file = NULL;
    file = fopen(Caminho, "w");
    return file;
}

FILE *RetornaHeatMap(tArquivos jogoArquivo){
    return jogoArquivo.Heatmap;
}

FILE *RetornaRanking(tArquivos jogoArquivo){
    return jogoArquivo.Ranking;
}

FILE *RetornaResumo(tArquivos jogoArquivo){
    return jogoArquivo.Resumo;
}

FILE *RetornaEstatisticas(tArquivos jogoArquivo){
    return jogoArquivo.Estatisticas;
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