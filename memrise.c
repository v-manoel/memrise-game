#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

//Table Size
#define LINES 4
#define COLUMNS 8
#define NAME_SIZE 30

//Global Variables
char table[LINES][COLUMNS]; //pairs of cards matrix (solution matrix)
char printTable[LINES][COLUMNS]; //masked cards matrix (printable)
int difficultTime = 8000;
int cheat1 = 0;
int cheat2 = 0;

//Consts
int PL1_CHEAT_CODE = 12345;
int PL2_CHEAT_CODE = 12345; 

//functions
void MixTable(); //fills and randomize initial table
int Menu(); //Menu with game options
short MoveValidate(); //validates players moves
void ReMaskTable(const int card1, const int card2); //updates printTable with hits mask
void HackPrint(); //prints solution matrix, if the cheat code was used
void GuidePrint(); //Shows game rules
void TablePrint(char generic_table[LINES][COLUMNS]); //Prints a table with LINES and COLUMNS dimension
void ClearBySys();
void FlushIn();



void main(){
    setlocale(LC_ALL, "portuguese");


    if(Menu() == 1){
        char pl1_name[NAME_SIZE], pl2_name[NAME_SIZE];
        unsigned finishCount, pl1_hits, pl2_hits;
        finishCount = pl1_hits = pl2_hits = 0;
        
        MixTable();
        FlushIn();
        printf("\t\t  !!!PARA COMEÇAR O JOGO OS JOGADORES DEVEM SE IDENTIFICAR!!!\n\n\t       \t\tPOR FAVOR CELEBRES JOGADORES NOS DIGAM SEUS NOMES:\n\n");
        printf("\nSOBERANO, PLAYER 1 DIGITE SEU NOME: ");
        scanf("%[^\n]", pl1_name);
        FlushIn();
        printf("\nSUPREMO, PLAYER 2 DIGITE SEU NOME: ");
        scanf("%[^\n]", pl2_name);
        //FlushIn();
        ClearBySys();

        printf("\t %s É O PARTICIPANTE NUMERO 1 DO JOGO\n\t %s É O PARTICIPANTE NÚMERO 2 DO JOGO\n",pl1_name,pl2_name);
        FlushIn();
        sleep(5);
        ClearBySys();
        printf("\t\t     !!!!GRAVE O QUANTO PUDER HAHAHA!!!!\n\n\t\t       !!!!QUE OS JOGOS COMECEM!!!!\n");
        TablePrint(table);
        printf("\n");
        sleep(difficultTime);
        ClearBySys();

        while (finishCount < (LINES * COLUMNS)/2){
            int validate = 1;
            printf("\n\t\t\tVEZ DO JOGADOR 1 - %s",pl1_name);
            while(validate && finishCount < (LINES * COLUMNS)/2){
                ClearBySys();
                TablePrint(printTable);

                if(cheat1==PL1_CHEAT_CODE){
                    printf("\n\t\t    PARECE QUE ALGUEM CONHECE AS REGRAS DO JOGO\n\n");
                    HackPrint();
	            }

                printf("\n\t\t\tINDICAÇÕES DE CARTAS\n");
                printf("\n\t\t\tSOBERANO %s ESCOLHA SUAS CARTAS:\n\n",pl1_name);
                validate=MoveValidate();

                if(validate == 1){
                    pl1_hits++;
                }
                sleep(10);
                ClearBySys();
                finishCount = pl1_hits + pl2_hits;
            }
  
            validate = 1;
            printf("\n\t\t\tVEZ DO JOGADOR 2 - %s",pl2_name);
            while(validate && finishCount < (LINES * COLUMNS)/2){
                TablePrint(printTable);

                if(cheat2==PL2_CHEAT_CODE){
                    printf("\n\t\t    PARECE QUE ALGUEM CONHECE AS REGRAS DO JOGO\n\n");
                    HackPrint();
	            }

                printf("\n\t\t\tINDICAÇÕES DE CARTAS\n");
                printf("\n\t\t\tSOBERANO %s ESCOLHA SUAS CARTAS:\n\n",pl2_name);
                validate=MoveValidate();
                printf("%d",validate);
                if(validate == 1){
                    pl2_hits++;
                }
                sleep(10);
                ClearBySys();
                finishCount = pl1_hits + pl2_hits;
            }
        }

         if(pl1_hits>pl2_hits)
            printf("\n\t\t  PARABÉNS SOBERANO %s VOCÊ GANHOU O JOGO\n\t\t  OBTEVE INCRÍVEIS %d ACERTOS",pl1_name,pl1_hits);
        else{
            if(pl1_hits<pl2_hits)
            printf("\n\t\t  PARABÉNS SUPREMO %s VOCÊ GANHOU O JOGO\n\t\t OBTEVE INCRÍVEIS %d ACERTOS",pl2_name,pl2_hits);
            else{
                printf("\n\t\t  AS HABILIDADES DOS SENHORES SÃO IMPRESSIONANTES - O JOGO EMPATOU");
            }
        }
        printf("\n\t\t  OBRIGADO POR JOGAR O ALFABETIC MEMORY GAME MEUS SENHORES");

        
    }else{
        printf("\n\t\t  OK! VOLTE QUANDO TIVER MAIS SENSO CRITICO");
    }

}


void TablePrint(char generic_table[LINES][COLUMNS]){

	printf("\n");
    unsigned i = 0;
    for (i = 0; i < LINES; i++)
    {
        printf("\t\t  ---------------------------------------\n");
        printf("\t\t  | %c || %c || %c || %c || %c || %c || %c || %c |\n", generic_table[i][0], generic_table[i][1], generic_table[i][2], generic_table[i][3], generic_table[i][4], generic_table[i][5], generic_table[i][6], generic_table[i][7]);
    }
    printf("\t\t  ----------------------------------------\n");
}

void MixTable(){
    /*cards[32]={33,35,36,37,38,63,60,61,64,126,157,168,169,184,188,241,33,35,36,37,38,63,60,61,64,126,157,168,169,184,188,241};*/
    int cards[LINES * COLUMNS]={'a','b','c','d','e','f','g','h','i','j','k','l','m','o','p','q','a','b','c','d','e','f','g','h','i','j','k','l','m','o','p','q'};

    int aux,r=0;
    aux=0;
    srand(time(NULL));
    unsigned i = 0;
    for(i=0;i<LINES*COLUMNS;i++){
    r=rand()%LINES*COLUMNS;
    aux=cards[i];
    cards[i]=cards[r];
    cards[r]=aux;
    }

    aux=0;
    unsigned j = 0;
    for (i = 0; i < LINES; i++)
    {
        for (j = 0; j < COLUMNS; j++)
        {
            table[i][j] = cards[aux++];
            printTable[i][j] = ' ';
        }
    }
}

void FlushIn(){ 
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}

void ClearBySys(){
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
//add some other OSes here if needed
#else
    #error "OS not supported."
    //you can also throw an exception indicating the function can't be used
#endif
}

short MoveValidate(){
    int line1,line2,col1,col2;
    int num1,num2;
    num1=0;
    num2=0;
    int card1;
    int card2;

    unsigned i = 0;
    unsigned j = 0;
    
    printf("\n");
    for(i=0;i<4;i++){
        printf("\t\t  ");
        for(j=0;j<8;j++){
            printf(" [%d%d]",num1,num2);
            num2++;
            if(num2>9){
            num2=0;
            num1++;
            }
        }
        printf("\n");
    }
    
    printf("\n");
    printf("\n\t\t  POR FAVOR MEU AMO, DIGITE A POSIÇÃO DAS CARTAS:\n");
    printf("A CARTA 1 É: ");
    scanf(" %d",&card1);
    printf("A CARTA 2 É: ");
    scanf(" %d",&card2);
    sleep(3);
    ClearBySys();
    //transforma�ao da posicao da carta em variavel
    line1=card1/8;
    line2=card2/8;
    col1=card1%8;
    col2=card2%8;


    if(card1==card2){
        printf("\n\n\n\n\t\t  !!!!MEU CARO, VOCÉ NÃO PODE ESCOLHER A MESMA CARTA!!!!\n");
        printf("\n\t\t  !!!!PENALIDADE A VEZ AGORA É DO OUTRO JOGADOR!!!!\n");
   
    }
    if(line1<4 && col1<8 && line2<4 && col2<8){
        if(printTable[line1][col1]!='X' && printTable[line2][col2]!='X'){
            ReMaskTable(card1, card2);
            if(table[card1/8][card1%8]==table[card2/8][card2%8] && card1!=card2)
                return 1;

        }
        else{
            printf("\n\n\n\n\t\t  !!!!MEU SENHOR, O SENHOR ESCOLHEU POSIÇÕES INVALIDAS!!!!\n");
            printf("\n\t\t  !!!!PENALIDADE A VEZ AGORA É DO OUTRO JOGADOR!!!!\n");
           
        }
    }
    else{
        printf("\n\t\t  INFELIZMENTE ESTAS SÃO COORDENADAS INVALIDAS\n");
        printf("\n\\t\t  !!!!SEREI BENEVOLENTE - TENTE OUTRA VEZ!!!!\n");
        ReMaskTable(card1, card2);
        return 2;
    }

    return 0;
}

void  HackPrint(){
    TablePrint(table);
}

int Menu(){
    char op;
    int ler;
    int level;
    printf("\t\t  !!!!BEM VINDO AO ALFABETIC MEMORY GAME!!!!\n\n");
    printf("\t\t\t      Pressione space\n\n\t\t\t  qualquer outra para sair: ");
    scanf("%c", &op);
    ClearBySys();
    printf("\t\t  DESEJA LER O MANUAL DO PEQUENO GARFANHOTO AVENTUREIRO?\n(1)SIM;\n(2)NÃO;\nDIGITE SUA SABIA ESCOLHA: ");
    scanf(" %d", &ler);
    if (ler == 1)
    {
        ClearBySys();
        GuidePrint();
        sleep(120);
        ClearBySys();
    }
    else
    {
        ClearBySys();
    }
    printf("\t\t  ESCOLHA A DIFICULDADE\n\n\t\t  (1)Easy;\n\t\t  (2)Normal;\n\t\t  (3)Hard;\nDigite:");
    scanf(" %d", &level);
    switch (level)
    {
    case 1:
        difficultTime = 15;
        break;
    case 2:
        difficultTime = 8;
        break;
    case 3:
        difficultTime = 2;
        break;
    }
    
    ClearBySys();
    printf("\t\t  POSSUI ALGUM CÓDIGO DE CHEAT JOGADOR 1? \n\t\t  DIGITE SEU CÓDIGO: ");
    scanf("%d", &cheat1);
    if (cheat1 == PL1_CHEAT_CODE){
        printf("MUITO BEM, VEJO QUE É UM JOGADOR SÁBIO - APROVEITE");
       
    }else{
    
        printf("DESCULPE, MAS PARECE QUE VOCE NÃO TEM O PASSAPORTE DOS DEUSES");
        
    }
    sleep(5);
    ClearBySys();
    printf("\t\t  POSSUI ALGUM CÓDIGO DE CHEAT JOGADOR 2? \n\t\t  DIGITE SEU CÓDIGO: ");
    scanf("%d", &cheat2);
    if (cheat2 == PL2_CHEAT_CODE){
        printf("MUITO BEM, VEJO QUE É UM JOGADOR SÁBIO - APROVEITE");
        
    }else{
        printf("DESCULPE, MAS PARECE QUE VOCE NÃO TEM O PASSAPORTE DOS DEUSES");
        
    }
    ClearBySys();
    if (op == ' ')
    {
        return 1;
    }
    else
    {
        return 0;
    }
    ClearBySys();
}

void ReMaskTable(const int card1, const int card2){
	
    printTable[card1/8][card1%8]=table[card1/8][card1%8];
    printTable[card2/8][card2%8]=table[card2/8][card2%8];

    TablePrint(printTable);
    if(table[card1/8][card1%8]==table[card2/8][card2%8] && card1!=card2){
        printTable[card1/8][card1%8]=table[card1/8][card1%8]='X';
        printTable[card2/8][card2%8]=table[card2/8][card2%8]='X';
        printf("\n\t     PARABÉNS VOCÊ ACERTOU UM PAR - POR ISSO PODE JOGAR DENOVO \n");
        sleep(5);
    }
    else{
        if(printTable[card1/8][card1%8]!='X' || card1==card2)
        printTable[card1/8][card1%8]=' ';
        if(printTable[card2/8][card2%8]!='X' || card1==card2)
        printTable[card2/8][card2%8]=' ';}
}

void GuidePrint(){
    printf("\t\t\t\t\t  !!!!BEM VINDO AO ALFABETIC MEMORY GAME!!!!\n\n\n\n");
    printf("\t     BEM VINDO JOVEM AVENTUREIRO, AO AURÉLIO DO ALFABETIC, AQUI VOCÊ APRENDERÁ O SENTIDO DA VIDA\n\tQUAL O PROPOSITO DA SUA EXISTÊNCIA E TAMBÁM COMO FUNCIONA O UNIVERSO DO ---ALAFABETIC MEMRORY GAME--- \n\t\t\t\t         TALVEZ MAIS A SEGUNDA COISA QUE A PRIMEIRA\n\n\t          BEM A PRIMEIRA COISA QUE VOCE DEVE SABER E QUE O JOGO E COMPOSTO DE TRÁS DIFICULDADES\n\t\t\t ELAS DETERMINARAM A QUANTIDADE DE TEMPO QUE VOCÊ TERÁ PARA VER AS CARTAS\n\t\t\t\t\t DICA:(BONS JOGADORES USAM APENAS O HARD)\n\n\t       HÁ PORÉM UM CÓDIGO ESPECIAL QUE LHE GARANTIRÁ ACESSO A TABELA VERDADE DURANTE TODO O GAME\n\t\t\t  ENTRETANTO OS DEVs NUNCA LHE DARÃO A CHAVE(HAHAHA NOS SOMOS OS DEVs)\n\n     BEM A SEGUNDA COISA QUE DEVE SABER E QUE VOCE DEVERÁ ESCOLHER AS CARTAS BASEANDO-SE NA MATRIZ DE INDICAÇÃOO\n\t   ELA LHE AJUDARÁ A DECIDIR QUAL A POSIÇÃO DAS CARTAS DESEJADAS - E NÃO HÁ PROBLEMA DIGITAR 07 OU 7 -\n\n      O JOGO ACABARA QUANDO OS 16 PARES FOREM ENCONTRADOS E ENTAO SERÁ EXIBIDO QUEM ACERTOU MAIS PARES DE CARTAS\n\n\n\n\n\t\t\t\t            ---UMA HOMENAGEM A INÊS RESTOVIC---\n\n\t\t\t\t\t          DEVELOPED BY VITOR E NEGHO");
}