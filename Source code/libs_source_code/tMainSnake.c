#include "../libs_h/tMainSnake.h"

//==========INICIALIZACAO/LEITURA=====//

tJogo LeMapa(char nomeDiretorio[], tJogo jogo){
    FILE *fmapa, *fInicializacao, *fsaida;
    int i, j;
    char CaminhoArquivosDeEntrada[1000];
    char CaminhoArquivoSaidaInicializacao[1000];

    //--Edicao do nome do caminho do arquivo de mapa--//
    CaminhoArquivosDeEntrada[0] = '\0';
    CaminhoArquivoSaidaInicializacao[0] = '\0';

    strcat(CaminhoArquivosDeEntrada, nomeDiretorio);
    strcat(CaminhoArquivosDeEntrada, "/mapa.txt");
    strcat(CaminhoArquivoSaidaInicializacao, nomeDiretorio);
    strcat(CaminhoArquivoSaidaInicializacao, "/saida/inicializacao.txt");

    //--Abertura dos arquivos para leitura ou escrita--//
    fmapa = fopen(CaminhoArquivosDeEntrada, "r");
    fInicializacao = fopen(CaminhoArquivoSaidaInicializacao, "w");

    //--Edicao dos arquivos--//
    if (fmapa == NULL){
        printf("ERRO: Arquivo mapa.txt nao encontrado em %s", nomeDiretorio); 
        fclose(fInicializacao);
        fclose(fmapa);
        exit(0);
    }

    //--Leitura do mapa--//
    fscanf(fmapa, "%d %d", &jogo.TamanhoLinha, &jogo.TamanhoColuna);
    fscanf(fmapa, "%*c");//pula o caractere '\n'
    for (i = 0; i < jogo.TamanhoLinha; i++){
        for (j = 0; j < jogo.TamanhoColuna; j++) {
            fscanf(fmapa, "%c", &jogo.tabuleiro[i][j]);
            fprintf(fInicializacao, "%c", jogo.tabuleiro[i][j]);
            printf("%c", jogo.tabuleiro[i][j]);
        }
        printf("\n");
        fscanf(fmapa, "%*c"); // pula o \n do arquivo mapa.txt
        fprintf(fInicializacao, "\n");
    }

    //--Inicializacao da posicao da cobra--//
    jogo = PosicaoInicial(jogo);
    fprintf(fInicializacao, "A cobra comecara o jogo na linha %d e coluna %d\n", RetornaPosicaoAtualCobra(jogo.Cobra, 'L')+1, RetornaPosicaoAtualCobra(jogo.Cobra, 'C')+1);


    //--Fechamento dos arquivos--//
    fclose(fInicializacao);
    fclose(fmapa);
    return jogo;
}

tJogo PosicaoInicial(tJogo jogo){
    int Linha, Coluna;
    //--Varre o mapa até encontrar uma posicao inicial para a cobra--//
    for (Linha = 0; Linha < jogo.TamanhoLinha; Linha++) {
        for (Coluna = 0; Coluna < jogo.TamanhoColuna; Coluna++){
            if (jogo.tabuleiro[Linha][Coluna] == COBRA_DIREITA){
                jogo.Cobra = AtualizaCoordenadaAtualCobra(jogo.Cobra, Linha, Coluna);
            }
        }
    }
    return jogo;
}

int kbhit(){//Função para verificar se o usuário apertou alguma tecla.
    struct termios term;
    tcgetattr(0, &term);

    struct termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

void Sleep(int tempo){
    struct timespec ts;
    ts.tv_sec = tempo / 1000;
    ts.tv_nsec = (tempo % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

int EhMovimentoContrario(char direcao, char direcaoAnterior){
    if (direcao == UP && direcaoAnterior == DOWN || (direcao == DOWN && direcaoAnterior == UP) || (direcao == LEFT && direcaoAnterior == RIGHT) || (direcao == RIGHT && direcaoAnterior == LEFT)){
        return 1;
    }
    return 0;
}

tJogo LeMovimentos(tJogo jogo){
    char mov;
    Sleep(jogo.velocidade);//funcao que pausa a execucao por X ms.
    if(!kbhit()){//verifica se o usuario apertou alguma tecla.
        mov = jogo.movAnterior;
        jogo.Estatisticas = ArmazenaMovimento(jogo.Estatisticas, mov);
        return jogo;
    }
    mov = getchar();
    if(EhMovimentoContrario(mov, jogo.movAnterior)){
        mov = jogo.movAnterior;
    }
    jogo.movAnterior = mov; 
    jogo.Estatisticas = ArmazenaMovimento(jogo.Estatisticas, mov);
    printf("\n");
    return jogo;
}

tJogo InicializaValores(tJogo jogo){
    //--Reseta os valores de estatisticas--//
    jogo.Estatisticas = ResetaValores(jogo.Estatisticas);
    jogo.ContadorCorpo = 0;
    jogo.TemPortal = 0;
    jogo.velocidade = 1000;
    jogo.movAnterior = RIGHT;
    int n = 0;
    int i, j;

    //--Conta a quantidade de itens no mapa--//
    for (i = 0; i < jogo.TamanhoLinha; i++) {
        for (j = 0; j < jogo.TamanhoColuna; j++)  {
            if(jogo.tabuleiro[i][j] == PORTAL){
                jogo.TemPortal = 1;
                jogo.portalLinha[n] = i;
                jogo.portalColuna[n] = j; 
                n++;
            }
        }
    }
    //--Inicializa a primeira posicao da cobra no heatmap--//
    for(i=0; i<jogo.TamanhoLinha; i++){
        for(j=0; j<jogo.TamanhoColuna; j++){
            if(jogo.tabuleiro[i][j] == COBRA_DIREITA){
                jogo.HeatMap[i][j] = 0;
            }
        }
    }
    return jogo;
}

tJogo RealizaJogada(tJogo jogo){
    int i = 0;
    char inicio;

    printf("PRESSIONE PARA INICIAR O JOGO\n");
    if(scanf("%c", &inicio) == 1){
        printf("\n");
    }

    for (i = 0; i < 10000000; ++i){
        if (RetornaQtdComida(jogo.Estatisticas) == 0){
            EncerraJogo(1, jogo);//Encerra o jogo com sucesso.
        }
        jogo = LeMovimentos(jogo);
        jogo.Cobra = AtualizaPosicaoCobraAntesMovimento(jogo.Cobra, RetornaPosicaoAtualCobra(jogo.Cobra, 'L'), RetornaPosicaoAtualCobra(jogo.Cobra, 'C'));
        jogo.Estatisticas = AtualizaNumeroDoMovimento(jogo.Estatisticas, i);
        jogo.Estatisticas = AtualizaAumentouCorpo(jogo.Estatisticas, 0);
        jogo.Estatisticas = AtualizaAumentouDinheiro(jogo.Estatisticas, 0);
        jogo = GeraHeatMap(jogo); 

       if(RetornaMovimento(jogo.Estatisticas) == 'w' && jogo.tabuleiro[RetornaPosicaoAtualCobra(jogo.Cobra, 'L')][RetornaPosicaoAtualCobra(jogo.Cobra, 'C')] != COBRA_BAIXO){
            jogo = MoveParaCima(jogo);
        }else if(RetornaMovimento(jogo.Estatisticas) == 's' && jogo.tabuleiro[RetornaPosicaoAtualCobra(jogo.Cobra, 'L')][RetornaPosicaoAtualCobra(jogo.Cobra, 'C')] != COBRA_CIMA){
            jogo = MoveParaBaixo(jogo);
        }else if(RetornaMovimento(jogo.Estatisticas) == 'a' && jogo.tabuleiro[RetornaPosicaoAtualCobra(jogo.Cobra, 'L')][RetornaPosicaoAtualCobra(jogo.Cobra, 'C')] != COBRA_DIREITA){
            jogo = MoveParaEsquerda(jogo);
        }else if(RetornaMovimento(jogo.Estatisticas) == 'd' && jogo.tabuleiro[RetornaPosicaoAtualCobra(jogo.Cobra, 'L')][RetornaPosicaoAtualCobra(jogo.Cobra, 'C')] != COBRA_ESQUERDA){
            jogo = MoveParaDireita(jogo);
        }

        if(RetornaJaMoveuCorpo(jogo.Estatisticas) == 0){
            jogo = MoveCorpo(jogo);
        }
        jogo.Estatisticas = AtualizaJaMoveuCorpo(jogo.Estatisticas, 0);//reseta o valor para 0.
        ImprimeJogo(jogo);
        GeraResumo(RetornaAumentouDinheiro(jogo.Estatisticas), RetornaAumentouCorpo(jogo.Estatisticas), jogo);
    }
    return jogo;  
}

//============PORTAIS==============//

int EncontraPosPortal(int linha, int coluna, tJogo jogo){
    if(linha == jogo.portalLinha[0] && coluna == jogo.portalColuna[0]){
        return 0;
    }else if(linha == jogo.portalLinha[1] && coluna == jogo.portalColuna[1]){
        return 1;
    } return -1;
}

tJogo MovePeloPortal(tJogo jogo, int linhaDestino, int colunaDestino, char mov){
    //--Move a cobra de um portal (tunel) para outro e atualiza a sua posicao--//
    if(mov == 'c'){
        jogo.tabuleiro[linhaDestino][colunaDestino] = COBRA_CIMA;
    }else if(mov == 'b'){
        jogo.tabuleiro[linhaDestino][colunaDestino] = COBRA_BAIXO;
    }else if(mov == 'e'){
        jogo.tabuleiro[linhaDestino][colunaDestino] = COBRA_ESQUERDA;
    }else if(mov == 'd'){
        jogo.tabuleiro[linhaDestino][colunaDestino] = COBRA_DIREITA;
    }
    jogo.Cobra = AtualizaCoordenadaAtualCobra(jogo.Cobra, linhaDestino, colunaDestino);
    return jogo; 
}

tJogo VerificaCondicoesAntesMovPeloPortal(tJogo jogo, int linha, int coluna, int n, char mov){
    if(coluna > jogo.TamanhoColuna-1){
        coluna = 0;
    }else if(coluna < 0 ){
        coluna = jogo.TamanhoColuna-1;
    }else if(linha > jogo.TamanhoLinha-1){
        linha = 0;
    }else if(linha < 0){
        linha = jogo.TamanhoLinha-1;
    }

    jogo = TipoDeBonus(linha, coluna, jogo);

    if(EhPosicaoValida(linha, coluna, jogo)){
        jogo = MoveCorpo(jogo);
        jogo.Estatisticas = AtualizaJaMoveuCorpo(jogo.Estatisticas, 1);
        jogo = MovePeloPortal(jogo, linha, coluna, mov);

    }else if(EhUltimoCorpo(linha, coluna, jogo)){
        jogo = MoveCorpo(jogo);
        jogo.Estatisticas = AtualizaJaMoveuCorpo(jogo.Estatisticas, 1);
        jogo = MovePeloPortal(jogo,linha, coluna, mov);

    }else  if(EhBorda(linha, coluna, jogo) && linha == 0 && EhPosicaoValida(linha, coluna, jogo)){
        jogo = MovePeloPortal(jogo,linha, coluna, mov);

    }else{
        jogo = MovePeloPortal(jogo, linha, coluna, mov);
        EncerraJogo(0, jogo);
    }
    return jogo;
}

tJogo UsaPortal(int linha, int coluna, char mov, tJogo jogo){
    int n = EncontraPosPortal(linha, coluna, jogo);//n = 0 -> portal 1 //  n = 1 -> portal 2.

    if(n == 0){//inverte o valor de n para transportar a cobra para o outro portal.
        n = 1;
    }else n = 0;

    switch(mov){
        case 'c': 
            jogo = VerificaCondicoesAntesMovPeloPortal(jogo, jogo.portalLinha[n]-1, jogo.portalColuna[n], n, mov);
        break;
        case 'b':
            jogo = VerificaCondicoesAntesMovPeloPortal(jogo, jogo.portalLinha[n]+1, jogo.portalColuna[n], n, mov);
        break;
        case 'e':
            jogo = VerificaCondicoesAntesMovPeloPortal(jogo, jogo.portalLinha[n], jogo.portalColuna[n]-1, n, mov);
        break;
        case 'd':
            jogo = VerificaCondicoesAntesMovPeloPortal(jogo, jogo.portalLinha[n], jogo.portalColuna[n]+1, n, mov);
        break;
    }
    return jogo;
}

int EhPortal(int linha , int coluna, tJogo jogo){
    if((linha == jogo.portalLinha[0] && coluna == jogo.portalColuna[0]) || (linha == jogo.portalLinha[1] && coluna == jogo.portalColuna[1])){
        return 1;
    } return 0;
}

//=========MOVIMENTOS=CABECA===============//

tJogo AtualizaPosicaoCobra(tJogo jogo, char mov){
    //--Atualiza e move (nessa ordem) a posicao da cabeca da cobra--//
    int PosicaoAtualCobraLinha = RetornaPosicaoAtualCobra(jogo.Cobra, 'L');
    int PosicaoAtualCobraColuna = RetornaPosicaoAtualCobra(jogo.Cobra, 'C');
    if(mov == 'c'){
        jogo.tabuleiro[--PosicaoAtualCobraLinha][PosicaoAtualCobraColuna] = COBRA_CIMA;
    }else if(mov == 'b'){
        jogo.tabuleiro[++PosicaoAtualCobraLinha][PosicaoAtualCobraColuna] = COBRA_BAIXO;
    }else if(mov == 'e'){
        jogo.tabuleiro[PosicaoAtualCobraLinha][--PosicaoAtualCobraColuna] = COBRA_ESQUERDA;
    }else jogo.tabuleiro[PosicaoAtualCobraLinha][++PosicaoAtualCobraColuna] = COBRA_DIREITA;

    jogo.Cobra = AtualizaCoordenadaAtualCobra(jogo.Cobra, PosicaoAtualCobraLinha, PosicaoAtualCobraColuna);
    return jogo;
}

tJogo ColocaComida(tJogo jogo){//coloca comida na posicao aleatoria do tabuleiro.
    int linha = rand()%jogo.TamanhoLinha;//gera uma posicao L aleatoria (de 0 a TamanhoLinha-1)
    int coluna = rand()%jogo.TamanhoColuna;//gera uma posicao C aleatoria (de 0 a TamanhoColuna-1)
    if(jogo.tabuleiro[linha][coluna] == ESPACO_LIVRE){
        jogo.tabuleiro[linha][coluna] = COMIDA;
    }else jogo = ColocaComida(jogo);
    return jogo;
}

tJogo TipoDeBonus(int linha, int coluna, tJogo jogo){
    int Tipo_De_Bonus = VerificaBonus(linha, coluna, jogo);
    //--Bonus = 1 -> bonus de Dinheiro--//
    //--Bonus = 2 -> bonus de Comida--//
    if(Tipo_De_Bonus == 1){
        jogo.Estatisticas = AtualizaPontuacao(jogo.Estatisticas, DINHEIRO);
    }else if(Tipo_De_Bonus == 2){
        jogo.Estatisticas = AtualizaPontuacao(jogo.Estatisticas, COMIDA);
        
        if(jogo.velocidade < 600){
            jogo.velocidade -=20;
        }else if(jogo.velocidade<300){
            jogo.velocidade -=10;
        }else{
           jogo.velocidade -= 35; 
        }
    
        jogo = ColocaComida(jogo);//coloca comida em posicao aleatoria do mapa
    }
    return jogo;
}

int VaiTeleportarCobra(tJogo jogo, int linha, int coluna, char mov){
    //--Verifica se a posicao atual eh BORDA VALIDA de acordo com o movimento dado--//
    if(mov == 'c'){
        if(EhBorda(linha, coluna, jogo) && linha == 0) return 1;
    }else if(mov == 'b'){
        if(EhBorda(linha, coluna, jogo) && linha == jogo.TamanhoLinha-1) return 1;
    }else if(mov == 'e'){
        if(EhBorda(linha, coluna, jogo) && coluna == 0) return 1;
    }else if(EhBorda(linha, coluna, jogo) && coluna == jogo.TamanhoColuna-1) return 1; 
    return 0;
}

tJogo MOVIMENTA_COBRINHA(tJogo jogo, int linha, int coluna, char mov){
    int linhaDestino, colunaDestino;//Usado caso vá teleportar.
    if(mov == 'c'){
        linhaDestino = jogo.TamanhoLinha-1;
        colunaDestino =RetornaPosicaoAtualCobra(jogo.Cobra, 'C');
    }else if(mov == 'b'){
        linhaDestino = 0;
        colunaDestino = RetornaPosicaoAtualCobra(jogo.Cobra, 'C');
    }else if(mov == 'e'){
        linhaDestino = RetornaPosicaoAtualCobra(jogo.Cobra, 'L');
        colunaDestino = jogo.TamanhoColuna-1;
    }else{
        linhaDestino = RetornaPosicaoAtualCobra(jogo.Cobra, 'L');
        colunaDestino = 0;
    }

    jogo = TipoDeBonus(linha, coluna, jogo);//Verifica se eh bonus e atualiza pontuacao.

    if(jogo.TemPortal == 1 && EhPortal(linha, coluna, jogo)){
        jogo = UsaPortal(linha, coluna, mov, jogo);
 
    }else if(EhPosicaoValida(linha, coluna, jogo)){//Vertifica a proxima celula .
        jogo = AtualizaPosicaoCobra(jogo, mov);

    }else  if(EhUltimoCorpo(linha, coluna, jogo)){//Caso particular -> PROX CELULA == ULTIMO CORPO.
        jogo = MoveCorpo(jogo);
        jogo.Estatisticas = AtualizaJaMoveuCorpo(jogo.Estatisticas, 1);//Corpo ja mexido.
        jogo = AtualizaPosicaoCobra(jogo, mov);

    }else  if(VaiTeleportarCobra(jogo, RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L'), RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C'), mov)){//Verifica se vai teleportar.
        
        if(EhPosicaoValida(linhaDestino, colunaDestino, jogo)){//Verifica as coordenadas de destino.
            jogo = TipoDeBonus(linhaDestino,colunaDestino, jogo);//Verifica bonus e atualiza pontuacao

            if(EhPortal(linhaDestino, colunaDestino, jogo) && jogo.TemPortal == 1){
                jogo = UsaPortal(linhaDestino, colunaDestino, mov, jogo);
                
            }else jogo = TeletransportaCobrinha(mov, jogo); 
            
        }else if(EhUltimoCorpo(linhaDestino, colunaDestino, jogo)){
            jogo = MoveCorpo(jogo);
            jogo.Estatisticas = AtualizaJaMoveuCorpo(jogo.Estatisticas, 1);//Corpo ja mexido.
            jogo = TeletransportaCobrinha(mov, jogo);

        }else{
            jogo = TeletransportaCobrinha(mov, jogo);
            EncerraJogo(0, jogo); 
        }

    }else{//Caso proxima celula seja invalida em todas as situações.
        jogo.tabuleiro[RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L')][RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C')] = ESPACO_LIVRE;
        jogo = AtualizaPosicaoCobra(jogo, mov);
        EncerraJogo(0, jogo);
    }
    return jogo;
}

tJogo MoveParaCima(tJogo jogo){
    //--Atualiza estatisticas e passa parametros para a funcao de movimento--//
    jogo.Estatisticas = AtualizaQtdMov(jogo.Estatisticas, 'c');
    jogo = MOVIMENTA_COBRINHA(jogo, RetornaPosicaoAtualCobra(jogo.Cobra, 'L')-1, RetornaPosicaoAtualCobra(jogo.Cobra, 'C'), 'c');
    return jogo;
}

tJogo MoveParaBaixo(tJogo jogo){
    //--Atualiza estatisticas e passa parametros para a funcao de movimento--//
    jogo.Estatisticas = AtualizaQtdMov(jogo.Estatisticas, 'b');
    jogo = MOVIMENTA_COBRINHA(jogo,RetornaPosicaoAtualCobra(jogo.Cobra, 'L')+1, RetornaPosicaoAtualCobra(jogo.Cobra, 'C'), 'b');
    return jogo;
}

tJogo MoveParaEsquerda(tJogo jogo){
    //--Atualiza estatisticas e passa parametros para a funcao de movimento--//
    jogo.Estatisticas = AtualizaQtdMov(jogo.Estatisticas, 'e');
    jogo = MOVIMENTA_COBRINHA(jogo, RetornaPosicaoAtualCobra(jogo.Cobra, 'L'), RetornaPosicaoAtualCobra(jogo.Cobra, 'C')-1, 'e');
    return jogo;
}

tJogo MoveParaDireita(tJogo jogo){
    //--Atualiza estatisticas e passa parametros para a funcao de movimento--//
    jogo.Estatisticas = AtualizaQtdMov(jogo.Estatisticas, 'd');
    jogo = MOVIMENTA_COBRINHA(jogo, RetornaPosicaoAtualCobra(jogo.Cobra, 'L'), RetornaPosicaoAtualCobra(jogo.Cobra, 'C')+1, 'd');
   return jogo;  
}

tJogo TeletransportaCobrinha(char mov, tJogo jogo){
    //--Teleporta a cobra para outra extremidade do mapa de acordo com o movimento dado--//
    int PosicaoAtualCobraLinha = RetornaPosicaoAtualCobra(jogo.Cobra, 'L');
    int PosicaoAtualCobraColuna = RetornaPosicaoAtualCobra(jogo.Cobra, 'C');
    if(mov == 'c'){
        jogo.tabuleiro[0][PosicaoAtualCobraColuna] = ESPACO_LIVRE;
        jogo.tabuleiro[jogo.TamanhoLinha - 1][PosicaoAtualCobraColuna] = COBRA_CIMA;
        jogo.Cobra = AtualizaCoordenadaAtualCobra(jogo.Cobra, jogo.TamanhoLinha-1, PosicaoAtualCobraColuna);
    }else if(mov == 'b'){
        jogo.tabuleiro[PosicaoAtualCobraLinha][PosicaoAtualCobraColuna] = ESPACO_LIVRE;
        jogo.tabuleiro[0][PosicaoAtualCobraColuna] = COBRA_BAIXO;
        jogo.Cobra = AtualizaCoordenadaAtualCobra(jogo.Cobra, 0, PosicaoAtualCobraColuna);
    }else if(mov == 'e'){
        jogo.tabuleiro[PosicaoAtualCobraLinha][PosicaoAtualCobraColuna] = ESPACO_LIVRE;
        jogo.tabuleiro[PosicaoAtualCobraLinha][jogo.TamanhoColuna - 1] = COBRA_ESQUERDA;
        jogo.Cobra = AtualizaCoordenadaAtualCobra(jogo.Cobra, PosicaoAtualCobraLinha, jogo.TamanhoColuna-1);
    }else if(mov == 'd'){
        jogo.tabuleiro[PosicaoAtualCobraLinha][PosicaoAtualCobraColuna] = ESPACO_LIVRE;
        jogo.tabuleiro[PosicaoAtualCobraLinha][0] = COBRA_DIREITA;
        jogo.Cobra = AtualizaCoordenadaAtualCobra(jogo.Cobra, PosicaoAtualCobraLinha, 0);
    }
    return jogo;
}

//================CORPO===================//

tJogo MoveCorpo(tJogo jogo){  
    /*
    A)QtdCorpo = 1 e Comeu comida:
    --> Mantém o corpo na mesma posição e coloca 'o' na posição anterior à cabeça.
    */
    if(RetornaQtdCorpoCobra(jogo.Estatisticas)==1 && RetornaAumentouCorpo(jogo.Estatisticas) == 1){
        jogo.tabuleiro[RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L')][RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C')] = CORPO; 

        jogo.Cobra = AtualizaUltimoCorpo(jogo.Cobra, RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L'), RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C'));
        
        jogo.CoordenadaLinhaCorpo[jogo.ContadorCorpo] = RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L');
        jogo.CoordenadaColunaCorpo[jogo.ContadorCorpo] = RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C');
    }

    /*
    B)QtdCorpo = 1 e Nao Comeu comida:
    --> Célula do corpo = espaço vazio; célula atual da cabeça = corpo;
    */
    else if(RetornaQtdCorpoCobra(jogo.Estatisticas)==1 && RetornaAumentouCorpo(jogo.Estatisticas) ==  0){
        jogo.CoordenadaLinhaCorpo[jogo.ContadorCorpo] = RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L');
        jogo.CoordenadaColunaCorpo[jogo.ContadorCorpo] = RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C');

        jogo.tabuleiro[RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L')][RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C')] = CORPO;

        jogo.tabuleiro[RetornaUltimoCorpo(jogo.Cobra, 'L')][RetornaUltimoCorpo(jogo.Cobra, 'C')] = ESPACO_LIVRE;
        //Atualiza a posição do último corpo.
        jogo.Cobra = AtualizaUltimoCorpo(jogo.Cobra, RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L'), RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C'));
    }

    /*
    C)QtdCorpo>1 e Comeu comida:
    --> Mantém o corpo no mesmo lugar; coloca 'o' na célula anterior à cabeça (vazia);
    --> Registra coordenada do corpo inserido;
    */
    else if(RetornaQtdCorpoCobra(jogo.Estatisticas)>1 && RetornaAumentouCorpo(jogo.Estatisticas) == 1){
        jogo.tabuleiro[RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L')][RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C')] = CORPO; 
        jogo.ContadorCorpo++;
        jogo.CoordenadaLinhaCorpo[jogo.ContadorCorpo] = RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L');
        jogo.CoordenadaColunaCorpo[jogo.ContadorCorpo] = RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C');
    }
    
    /*
    D)QtdCorpo>1 e Nao comeu comida;
    --> Move Corpo e atualiza a posição do último corpo.
    */
    else if(RetornaQtdCorpoCobra(jogo.Estatisticas)>1 && RetornaAumentouCorpo(jogo.Estatisticas) == 0){
        jogo = AtualizaCoordenadasCorpo(jogo);
    }   
    
    /*
    E)QtdCorpo = 0; -> Célula anterior à cabeça = vazio;
    */
    if(RetornaQtdCorpoCobra(jogo.Estatisticas) == 0){
        jogo.tabuleiro[RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L')][RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C')] = ESPACO_LIVRE;
    }
    return jogo;
}

tJogo AtualizaCoordenadasCorpo(tJogo jogo){
    int i;
    
    //Coordenada corpo[0] = Coordenada corpo[1] .... de 0 a n-1
    for(i=0; i<RetornaQtdCorpoCobra(jogo.Estatisticas); i++){
        jogo.CoordenadaLinhaCorpo[i] = jogo.CoordenadaLinhaCorpo[i+1];
        jogo.CoordenadaColunaCorpo[i] = jogo.CoordenadaColunaCorpo[i+1];
    }

    //Coordenada do corpo [n-1] = Coordenada da célula anterior à cabeça.
    jogo.CoordenadaLinhaCorpo[RetornaQtdCorpoCobra(jogo.Estatisticas)-1] = RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L');
    jogo.CoordenadaColunaCorpo[RetornaQtdCorpoCobra(jogo.Estatisticas)-1] = RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C');

    //Limpa célula onde estava o último corpo.
    jogo.tabuleiro[RetornaUltimoCorpo(jogo.Cobra, 'L')][RetornaUltimoCorpo(jogo.Cobra, 'C')] = ESPACO_LIVRE;

    //Coloca 'o' na posição anterior à cabeça.
    jogo.tabuleiro[RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L')][RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C')] = CORPO;

    //Atualiza coordenada do último corpo.
    jogo.Cobra = AtualizaUltimoCorpo(jogo.Cobra, jogo.CoordenadaLinhaCorpo[0], jogo.CoordenadaColunaCorpo[0]);
    return jogo;
}

//================VERIFICACAO=================//

int EhBorda(int linha, int coluna, tJogo jogo){
    if(linha == 0 || coluna == 0 || linha == jogo.TamanhoLinha -1  || coluna == jogo.TamanhoColuna-1 ){
        return 1;
    }
    return 0;
}

int VerificaBonus(int linha, int coluna, tJogo jogo){
    //--Verifica se na posicao seguinte existe um bonus--//
    if(jogo.tabuleiro[linha][coluna] == DINHEIRO){
        return 1;
    }else if(jogo.tabuleiro[linha][coluna] == COMIDA){
        return 2;
    }return 0;
}

int EhPosicaoValida(int linha, int coluna, tJogo jogo){
    //--Verifica se a posicao seguinte esta dentro do tamanho do mapa e se eh celula valida--//
    if((jogo.tabuleiro[linha][coluna] != PAREDE && jogo.tabuleiro[linha][coluna] != CORPO && linha<jogo.TamanhoLinha && coluna<jogo.TamanhoColuna && linha>=0 && coluna>=0)){
        return 1;
    } return 0;
}

int EhUltimoCorpo(int linha, int coluna, tJogo jogo){
    if(linha == jogo.CoordenadaLinhaCorpo[0] && coluna == jogo.CoordenadaColunaCorpo[0]){
        return 1;
    }
    return 0;
}

//=============PRINT/FIM=====================//

void ImprimeJogo(tJogo jogo){
    int i, j;
    for (i = 0; i < jogo.TamanhoLinha; i++){
        for (j = 0; j < jogo.TamanhoColuna; j++){
            printf("%c", jogo.tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("Pontuacao: %d\n", RetornaPontuacao(jogo.Estatisticas));
}

void MataCobrinha(tJogo jogo){
    //--Coloca X em todas as posicoes do corpo da cobra--//
    int i, j;
    for(i=0;i<jogo.TamanhoLinha;i++){
        for(j=0;j<jogo.TamanhoColuna;j++){
            if(jogo.tabuleiro[i][j] == COBRA_CIMA || jogo.tabuleiro[i][j] == COBRA_BAIXO || jogo.tabuleiro[i][j] == COBRA_ESQUERDA || jogo.tabuleiro[i][j] == COBRA_DIREITA || jogo.tabuleiro[i][j] == CORPO){
                jogo.tabuleiro[i][j] = MORREU;
            }
        }
    }
    ImprimeJogo(jogo);
}

void EncerraJogo(int validador, tJogo jogo){
    //validador = 0 -> jogo encerrado porque a cobra morreu.
    //validador = 1 -> jogo encerrado porque o jogo acabou com sucesso.

    //--De acordo com o validador, atualiza os dados necessarios e encerra o jogo--//
    FILE *RESUMO = RetornaResumo(jogo.Arquivos);
    if(validador == 1){
        printf("Voce venceu!\nPontuacao final: %d\n", RetornaPontuacao(jogo.Estatisticas));
        jogo = GeraHeatMap(jogo); 
        ImprimeEstatisticas(jogo);
        ImprimeHeatMap(jogo);
        fclose(RESUMO);
        exit(EXIT_SUCCESS);
    }else{
        int TipoDeBonus = VerificaBonus(RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'L'), RetornaPosicaoCobraAntesMovimento(jogo.Cobra, 'C'), jogo);
        jogo = GeraHeatMap(jogo); 
        jogo = MoveCorpo(jogo);
        MataCobrinha(jogo);

        if(TipoDeBonus == 1){
            jogo.Estatisticas = AtualizaPontuacao(jogo.Estatisticas, DINHEIRO);
        }else if(TipoDeBonus == 2){
            jogo.Estatisticas = AtualizaPontuacao(jogo.Estatisticas, COMIDA);
        }

        fprintf(RESUMO, "Movimento %d (%c) resultou no fim de jogo por conta de colisao\n" ,RetornaNumeroDoMovimento(jogo.Estatisticas), RetornaMovimento(jogo.Estatisticas));
        printf("Game over!\nPontuacao final: %d\n", RetornaPontuacao(jogo.Estatisticas));

        ImprimeEstatisticas(jogo);
        ImprimeHeatMap(jogo);
        fclose(RESUMO);
        exit(EXIT_SUCCESS);
    }
}

void GeraResumo(int AumentouDinheiro, int AumentouCorpo, tJogo jogo){
    FILE *RESUMO = RetornaResumo(jogo.Arquivos);
    int NumeroDoMovimento = RetornaNumeroDoMovimento(jogo.Estatisticas);
    char mov = RetornaMovimento(jogo.Estatisticas);
    int QtdCorpo = RetornaQtdCorpoCobra(jogo.Estatisticas);
    
    //--Atualiza o resumo do jogo a cada movimento--//
    if(RetornaQtdComida(jogo.Estatisticas) == 0){
        fprintf(RESUMO, "Movimento %d (%c) fez a cobra crescer para o tamanho %d, terminando o jogo\n" ,NumeroDoMovimento, mov, QtdCorpo+1);
    }else if(AumentouCorpo){
        fprintf(RESUMO, "Movimento %d (%c) fez a cobra crescer para o tamanho %d\n" ,NumeroDoMovimento, mov, QtdCorpo+1);
    }else if(AumentouDinheiro){
        fprintf(RESUMO, "Movimento %d (%c) gerou dinheiro\n" ,NumeroDoMovimento, mov);
    } 
}

void ImprimeEstatisticas(tJogo jogo){
    int QtdMovSemPontuar = RetornaQtdMov(jogo.Estatisticas) - RetornaQtdCorpoCobra(jogo.Estatisticas) - RetornaQtdDinheiro(jogo.Estatisticas);
    FILE *ESTATISTICAS = RetornaEstatisticas(jogo.Arquivos);
 
    fprintf(ESTATISTICAS, "Numero de movimentos: %d\nNumero de movimentos sem pontuar: %d\nNumero de movimentos para baixo: %d\nNumero de movimentos para cima: %d\nNumero de movimentos para esquerda: %d\nNumero de movimentos para direita: %d\n", RetornaQtdMov(jogo.Estatisticas), QtdMovSemPontuar, RetornaMovBaixo(jogo.Estatisticas), RetornaMovCima(jogo.Estatisticas), RetornaMovEsquerda(jogo.Estatisticas), RetornaMovDireita(jogo.Estatisticas));

    fclose(ESTATISTICAS);
}

tJogo GeraHeatMap(tJogo jogo){
    //--Gera a matriz das dimensoes do mapa com o num de vezes que a cobra passou pela posicao--//
    int i, j;
    for(i=0;i<jogo.TamanhoLinha;i++){
        for(j=0;j<jogo.TamanhoColuna;j++){
            if(jogo.tabuleiro[i][j] == COBRA_CIMA || jogo.tabuleiro[i][j] == COBRA_BAIXO || jogo.tabuleiro[i][j] == COBRA_ESQUERDA || jogo.tabuleiro[i][j] == COBRA_DIREITA){
                jogo.HeatMap[i][j]++;
            }
        }
    }
    return jogo;
}

void ImprimeHeatMap(tJogo jogo){
    //--Imprime o heatmap no arquivo de saida heatmap.txt--//
    int i, j;
    FILE *HEATMAP = RetornaHeatMap(jogo.Arquivos);

    for(i=0;i<jogo.TamanhoLinha;i++){
        for(j=0;j<jogo.TamanhoColuna;j++){
            fprintf(HEATMAP, "%d", jogo.HeatMap[i][j]);
            if(j != jogo.TamanhoColuna-1){
                fprintf(HEATMAP, " ");
            }
        }
        fprintf(HEATMAP, "\n");
    }
    GeraRanking(jogo);
    fclose(HEATMAP);
}

void GeraRanking(tJogo jogo){
    int i, j, MaiorHeatMap = 0;
    FILE *RANKING = RetornaRanking(jogo.Arquivos);

    //--Varre o heatmap e encontra o maior valor--//
    for(i=0;i<jogo.TamanhoLinha;i++){
        for(j=0;j<jogo.TamanhoColuna;j++){
            if(jogo.HeatMap[i][j] > MaiorHeatMap){
                MaiorHeatMap = jogo.HeatMap[i][j];
            }
        }
    }
    //--Imprime cada posicao do heatmap com o numero de vezes que a cobra passou pela posicao--//
    while(MaiorHeatMap>0){
        for(i=0;i<jogo.TamanhoLinha;i++){
            for(j=0;j<jogo.TamanhoColuna;j++){
                if(jogo.HeatMap[i][j] == MaiorHeatMap){
                    fprintf(RANKING, "(%d, %d) - %d\n", i, j, jogo.HeatMap[i][j]);
                }
            }
        }  
        MaiorHeatMap--;
    }    
    fclose(RANKING);
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