#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 9
#define espacamento 1 //Espaçamento da matriz na hora de mostrar

//Estrutura

struct grade
	{
		int valor;
		int ndisponiveis[9];          //Marca os numeros disponiveis
		int resolvido;               //0 - Caso não      1 - Caso sim
	};

int main()
{

	//Almoxarifado de funções

	void entradaArquivo(struct grade a[9][9]);
	void zeros(struct grade a[9][9]);
	void correcao(struct grade a[9][9]);
	void mostraAjudaEntrada(void);
	void mostraGrade(struct grade a[9][9]);

	void logica(struct grade casa[9][9]);

	//Almoxarifado de variáveis
	struct grade casa[9][9];
	int entrada;

	//Menu de entrada
	printf("\n\tMetodo de entrada:\n\t1 - Entrada por arquivo .txt\n\t2 - Entrada por coordenadas\n\t3 - Ajuda\n\n");

	reentrada:
	printf("\tEntrada: ");

	scanf("%d", &entrada);

	switch(entrada)
	{
		case 1:
		entradaArquivo(casa);
		break;

		case 2:
		zeros(casa);
		correcao(casa);
		break;

		case 3:
		mostraAjudaEntrada();
		goto reentrada;
		break;

		default:
		goto reentrada;
	}

	printf("\n");

	logica(casa);
	

	return 0;
}

//Entrada da matriz

void entradaArquivo(struct grade a[9][9])
{
	char letra;
	void correcao(struct grade a[9][9]);
	void mostraGrade(struct grade a[9][9]);

	FILE *arquivo;

	arquivo = fopen("entrada.txt", "r");
	//freopen("entrada.txt", "r", stdin);

	if(arquivo==NULL){printf("\nErro ao ler o arquivo 'entrada.txt'!\n:(\n\n");}

	for(int i = 0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			fscanf(arquivo, "%d", &a[i][j].valor);
		}
	} 

	printf("\n\tEstado de jogo atual:\n");
	mostraGrade(a);

	fclose(arquivo);

	printf("\n\tExigir correcao (Y/N)?\n");
	correcao:
	printf("\t>");	
	scanf(" %c", &letra);
	letra = toupper(letra);

	switch(letra)
	{
		case 'Y':
		correcao(a);
		break;

		case 'N':
		break;

		default:
		goto correcao;

	}
}

void zeros(struct grade a[9][9])
{
	//Definindo valor inicial nulo
	for(int i = 0; i<N; i++)
	{
		for(int j = 0; j<N; j++)
		{
			a[i][j].valor = 0;
		}
	}
}

void correcao(struct grade a[9][9])
{
	void mostraGrade(struct grade a[9][9]);

	printf("\n\tEntre na forma \"[valor] [linha],[coluna]\"\n\tPara finalizar entre com: 0 0,0\n");

	int i,j,m;

	while(1)
	{	
		printf("\n\t------------------------");
		//printf("\n\n\n\n\n\n\n\n\n\n");
		printf("\n\t>");
		scanf("%d %d,%d", &m, &i, &j);

		if(m==0)
		{
			break;
		}

		else
		{
			i--;
			j--;
			a[i][j].valor = m;
		}

		mostraGrade(a);
	}
}

void mostraAjudaEntrada(void)
{
	printf("\n\t1 - O programa le automaticamente a matriz salva no arquivo 'jogo.txt'\n");
	printf("\t2 - O usuario digita o valor e o indice das casas na matriz do jogo um a um a partir de uma matriz vazia\n\n");
}


void mostraGrade(struct grade a[9][9])
{	
	printf("\n");
	int j;

	for(int i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			if(j==3||j==6){printf(" ");}
			if(j==0){printf("\t");}
			printf("%*d ",espacamento , a[i][j].valor);
		}
		if(i==2||i==5){printf("\n");}
		printf("\n");
	}
}

//ABAIXO DESTAS LINHAS ACONTECEM A MAGIA DO PROGRAMA E TODA A SUA CONTEMPLAÇÃO E PUREZA
//DIANTE DA NATUREZA DA COMPUTAÇÃO. ESPERO QUE A PAZ SEJA ALCANÇADA NOS REINOS SUBLIMES DESTA NAÇÃO

int numerosLinha[18][9];   //Primeiro indice indica linha/bloco, o segundo indica os numeros contidos
int numerosBloco[9][9];

void logica(struct grade casa[9][9])
{
	void verificarErro(struct grade casa[9][9]);

	verificarErro(casa);
	printf("\n\tLivre de erros!\n");
	printf("\tResolvendo...\n");
}



void verificarErro(struct grade casa[9][9])
{
	int hasError = 0;

	corrigir:

	mostraGrade(casa);
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			int m = casa[i][j].valor;

			if(m!=0)
			{
				if(m>0 && m<10)
				{
					//Ver se ja existe add na linha
					for(int k=0; k<N;k++)
					{
						if(m==casa[i][k].valor && k!=j)
						{
							printf("\n\tErro de linha encontrado entre (%d,%d) e (%d,%d)!\n\n", i+1, j+1, i+1, k+1);
							
							printf("\tCorrija: (%d,%d) = ", i+1, j+1);
							scanf("%d", &casa[i][j].valor);

							printf("\tCorrija: (%d,%d) = ", i+1, k+1);
							scanf("%d", &casa[i][k].valor);

							goto corrigir;
						}
					}

					//Ver se ja existe add na coluna
					for(int k=0; k<N;k++)
					{
						if(m==casa[k][j].valor && k!=i)
						{
							printf("\n\tErro de coluna encontrado entre (%d,%d) e (%d,%d)!\n\n", i+1, j+1, k+1, j+1);
							
							printf("\tCorrija: (%d,%d) = ", i+1, j+1);
							scanf("%d", &casa[i][j].valor);

							printf("\tCorrija: (%d,%d) = ", k+1, j+1);
							scanf("%d", &casa[k][j].valor);

							
							goto corrigir;
						}
					}

					//Ver se ja existe no bloco

					//Definir o bloco
					int bloco;

					if(i<3)
					{
						if(j<3){bloco = 1;}
						else if(j<6){bloco = 2;}
						else{bloco = 3;}
					}

					else if(i<6)
					{
						if(j<3){bloco = 4;}
						else if(j<6){bloco = 5;}
						else{bloco = 6;}
					}

					else
					{
						if(j<3){bloco =7;}
						else if(j<6){bloco = 8;}
						else{bloco = 9;}
					}

					//Comparar com cada bloco
					int i1,i2,j1,j2;
					switch(bloco)
					{
						case 1:
						i1=0;i2=2;j1=0;j2=2;
						break;

						case 2:
						i1=0;i2=2;j1=3;j2=5;
						break;

						case 3:
						i1=0;i2=2;j1=6;j2=8;
						break;

						case 4:
						i1=3;i2=5;j1=0;j2=2;
						break;

						case 5:
						i1=3;i2=5;j1=3;j2=5;
						break;

						case 6:
						i1=3;i2=5;j1=6;j2=8;
						break;

						case 7:
						i1=6;i2=8;j1=0;j2=2;
						break;

						case 8:
						i1=6;i2=8;j1=3;j2=5;
						break;

						case 9:
						i1=6;i2=8;j1=6;j2=8;
						break;						
					}
					i2++;j2++;

					//Corrigir

					for(int p=i1; p<i2; p++)
					{
						for(int q=j1;q<j2;q++)
						{
							if(m==casa[p][q].valor && i!=p && j!=q)
							{
								printf("\n\tErro de bloco encontrado entre (%d,%d) e (%d,%d)\n",i+1, j+1, p+1,q+1);
								printf("\tCorrija: (%d,%d): ", i+1, j+1);
								scanf("%d", &casa[i][j].valor);

								printf("\tCorrija: (%d,%d): ", p+1, q+1);
								scanf("%d", &casa[p][q].valor);

								goto corrigir;
							}
						}
					}


				}

				else
				{	
					printf("\n\tNumero invalido em (%d,%d)\n", i+1,j+1);
					printf("\tCorrija: (%d,%d) = ", i+1, j+1);
					scanf("%d", &casa[i][j].valor);
					goto corrigir;
				}
			}

		}
	}
}