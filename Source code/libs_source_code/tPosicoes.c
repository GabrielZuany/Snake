#include "../libs_h/tPosicoes.h"

tCobra AtualizaPosicaoCobraAntesMovimento(tCobra JogoCobra, int linha, int coluna){
    JogoCobra.PosicaoCobraAntesMovimentoLinha = linha;
    JogoCobra.PosicaoCobraAntesMovimentoColuna = coluna;
    return JogoCobra;
}

tCobra AtualizaCoordenadaAtualCobra(tCobra JogoCobra, int linha, int coluna){
    JogoCobra.PosicaoAtualCobraLinha = linha;
    JogoCobra.PosicaoAtualCobraColuna = coluna;
    return JogoCobra;
}

tCobra AtualizaUltimoCorpo(tCobra JogoCobra, int linha, int coluna){
    JogoCobra.UltimaPosicaoLinhaCorpo = linha;
    JogoCobra.UltimaPosicaoColunaCorpo = coluna;
    return JogoCobra;
}

int RetornaPosicaoCobraAntesMovimento(tCobra JogoCobra, char id){
    if(id=='L') return JogoCobra.PosicaoCobraAntesMovimentoLinha;
    return JogoCobra.PosicaoCobraAntesMovimentoColuna;
}

int RetornaPosicaoAtualCobra(tCobra JogoCobra, char id){
    if(id == 'L')return JogoCobra.PosicaoAtualCobraLinha;
    return JogoCobra.PosicaoAtualCobraColuna;
}

int RetornaUltimoCorpo(tCobra JogoCobra, char tipo){
    if(tipo == 'L') return JogoCobra.UltimaPosicaoLinhaCorpo;
    return JogoCobra.UltimaPosicaoColunaCorpo;
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