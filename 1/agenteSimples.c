/******************************************************************************

O objetivo do agente A é capturar todos os . e os * da tela no menor tempo possivel.
Os * são mais atrativos para o agente que os .
1 - Escreva a função do agente seguindo o modelo reativo simples.
2 - Escreva a função do agente seguindo o modelo reativo baseado em modelos.
3 - Escreva a função do agente seguindo o modelo reativo baseado em objetivos.
4 - Escreva a função do agente seguindo o modelo reativo baseado na utilidade.

Depois compare o tempo que cada abordagem demorou para atingir o objetivo.

O agente capta com seus sensores o conteudo das 4 casas ao seu redor (esquerda, direita, cima, baixo)
O agente tem como acoes movimentar-se para esquerda (0), direita (1), cima (2), baixo (3)


*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 15

#define ESQUERDA 0
#define DIREITA 1
#define CIMA 2
#define BAIXO 3

int posAgenteX = 1;
int posAgenteY = 1;

int numPonto = 50;
int numAster = 50;
int numEspaco = 155;

int ambiente[SIZE][SIZE];

void delay(int tempo){
	for(int i=0; i<tempo; i++);
}

void construirAmbiente(){
    int temp;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
			if(i == 0 || i == SIZE-1){
				if(j == 0 || j == SIZE-1) ambiente[i][j] = 3;
				else ambiente[i][j] = 4;
			}
			else if(j == 0 || j == SIZE-1) ambiente[i][j] = 5;
			else {
                temp = rand()%3;
                if (temp == 0 && numEspaco > 0){
                    numEspaco--;
                }else if (temp == 1 && numPonto > 0){
                    numPonto--;
                }else if (temp == 2 && numAster > 0){
                    numAster--;
                }else{
                    j--;
                    continue;
                }
                ambiente[i][j] = temp;
            }
        }
    }
}


void atuarNoAmbiente(int acao){
    ambiente[posAgenteX][posAgenteY] = 0;
    if (acao == 0 && ambiente[posAgenteX][posAgenteY-1] < 3) posAgenteY -= 1;
    else if (acao == 1 && ambiente[posAgenteX][posAgenteY+1] < 3) posAgenteY += 1;
    else if (acao == 2 && ambiente[posAgenteX-1][posAgenteY] < 3) posAgenteX -= 1;
    else if (acao == 3 && ambiente[posAgenteX+1][posAgenteY] < 3) posAgenteX += 1;
    ambiente[posAgenteX][posAgenteY] = 6;
}    

void mostrarAmbiente(){
	system("clear");
	int count = 0;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if (ambiente[i][j] == 0) printf(" ");
            else if (ambiente[i][j] == 1) { count++; printf(".");}
            else if (ambiente[i][j] == 2) { count++; printf("*");}			
            else if (ambiente[i][j] == 3) printf("+");
            else if (ambiente[i][j] == 4) printf("-");
            else if (ambiente[i][j] == 5) printf("|");
            else if (ambiente[i][j] == 6) printf("A");
        }
        printf("\n");
    }
	printf("Faltam %d objetos.\n", count);
}

bool verificarSucesso(){
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if (ambiente[i][j] == 1 || ambiente[i][j] == 2) return false;
        }
    }
    return true;
}

int lerSensor(int lado){
    if (lado == ESQUERDA) return ambiente[posAgenteX][posAgenteY-1];
    if (lado == DIREITA) return ambiente[posAgenteX][posAgenteY+1];
    if (lado == CIMA) return ambiente[posAgenteX-1][posAgenteY];
    if (lado == BAIXO) return ambiente[posAgenteX+1][posAgenteY];
    return 2;
}

int funcaoAgenteSimples(int esquerda, int direita, int cima, int baixo){
	//reativo simples, preferência por *
	//delay(500);
	if(cima==2 ) return 2;
	if(direita==2) return 1;
	if(esquerda==2) return 0;
	if(baixo==2) return 3;
    
	if (cima==1) return 2;
    if (direita==1) return 1;
    if (esquerda==1) return 0;
    if (baixo==1) return 3;
    
    return rand()%4;
}

int main()
{
    clock_t tempo[2];
	construirAmbiente();
	mostrarAmbiente();
    
    tempo[0] = clock();
	while(!verificarSucesso()){
        int acao = funcaoAgenteSimples(lerSensor(0), lerSensor(1), lerSensor(2), lerSensor(3));
        atuarNoAmbiente(acao);
        mostrarAmbiente(); //mostra o que esta acontecendo, mas atrasa a execução
    }
	tempo[1] = clock();
    
	printf("Tempo gasto: %g ms.", ((tempo[1] - tempo[0]) / ((double)CLOCKS_PER_SEC)));
    return 0;
}