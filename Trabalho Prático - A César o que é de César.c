/**
**======================================
** Elementos de Programa��o
** Professor: Marcos Zuccolotto
** Alunos: Guilherme da Cunha Pioner e Pedro Stanislau Tomacheski
** Turma: 4311
** N�s: 6 e 21
**======================================
*/

/**
**=========================================================================================
** Trabalho Pr�tico - A C�sar o que � de C�sar
** Objetivo: Codificar um decifrador de mensagens utilizando a cifra de Cesar.
**
**=========================================================================================
*/

/*
**=========================================================================================
** Considera��es do c�digo:
** 
** O seguinte programa, desenvolvido pelos alunos Guilherme Pioner e Pedro Stanislau da
** turma 4311, consiste em um cifrador e decifrador da famosa Cifra de C�sar. O programa
** cont�m duas ferramentas claras que podem ser facialmente acessadas pelo menu do mesmo,
** sendo estas:
** -> Cifrador:
** O usu�rio escolhe um arquivo em que deseja armazenar uma mensagem criptografada, ap�s a
** escolha, ele deve inserir a mensagem que deseja mascarar com a Cifra de C�sar. Nesta 
** op��o, o usu�rio escolhe o deslocamento fixo.
**
** -> Decifrador:
** O usu�rio escolhe um arquivo .txt com uma mensagem j� criptografada. A mensagem deve 
** ser composta apenas por letras mai�sculas e n�o deve conter espa�os.
** Nesta fun��o, o programa indicar� as duas respostas mais prov�veis e o usu�rio deve
** escolher a correta. (Para encontrarmos quais as respostas mais prov�veis, usamos um
** sistema de pesos paras as letras mais incidentes na l�ngua portuguesa, onde as mais
** comuns t�m um peso maior, e as menos comuns t�m um peso menor. Quando essas letras
** aparecem, seus pesos s�o somados � uma soma geral para o deslocamento atual.
** Para descobrir as melhores respostas, basta procurar as mensagens deslocadas com o
** maior valor da soma geral, estas ser�o as mais prov�veis de estarem corretas.)
** A resposta da descriptografia estar� em um arquivo .txt cujo nome � igual ao do
** inserido pelo usu�rio, acrescido do sufixo "_dec".
**
** O programa, al�m do menu principal, cont�m um menu de inicializa��o onde o usu�rio
** pode selecionar se deseja, ou n�o, aprender como funciona a Cifra de C�sar.
**
** Fonte para as letras mais incidentes na l�ngua portuguesa:
** http://dicionariosvarios.blogspot.com/2013/07/percentuais-de-frequencia-de-letras-no.html
**=========================================================================================
*/



/* Prot�tipos */
int menu(void);			// Menu geral com as ferramentas do programa
int start_m(void);		// Menu de inicializa��o (s� aparece no in�cio do programa)

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <string.h>

void main(void)
{
	/* Configura��es prim�rias */
	setlocale(LC_ALL,"portuguese");		// Habilita caracteres da l�ngua portuguesa
	srand(time(NULL));					// Habilita a gera��o de n�meros rand�micos

	/* DECLARANDO AS VARI�VEIS */
	FILE *fp;				// Cria o ponteiro para arquivos
	char fname	 [50];		// String para o nome do arquivo
	char fname2	 [54] = { '_','d','e','c','.','t','x','t' };	// String para o nome do arquivo a ser criado
	char string	[200];		// String original
	char aux	[200];		// String de aux�lio
	char resp_1	[200];		// String para a primeira resposta mais prov�vel 
	char resp_2	[200];		// String para a segunda resposta mais prov�vel
	char cifrar	[200];		// String para a mensagem a ser cifrada
	int desloca[2] = {0};	// Array que armazena os deslocamentos das respostas mais prov�veis
	int maior[2]   = {0};	// Array que armazena os maiores valores de 'soma'
	int soma[26]   = {0};	// Array que armazena os pesos de cada deslocamento
	int cntrl 	   =  0;	// Vari�vel de controle para as op��es
	int tamanho    =  0;	// Vari�vel para o tamanho das strings
	int rot        =  0;	// Vari�vel que armazena o deslocamento da mensagem a ser cifrada
	int result     =  0;	// Vari�vel para aux�lio nos deslocamentos
	int i 		   =  0; 	
	int	j 		   =  0;	// Vari�veis de controle para os la�os de repeti��es
	/* DECLARANDO AS VARI�VEIS */
	
	cntrl = start_m();		// Chama o menu de come�o de programa.
	
	while(1)
	{	
		switch(cntrl)
		{
			case 1: 	// CIFRAR UMA MENSAGEM
				/* RECEBENDO O ARQUIVO */
				puts("Digite o nome do arquivo de texto desejado: ");
				gets(fname);
				strcat(fname,".txt");		// Adiciona o texto '.txt' ao final da string 'fname'
				fp=fopen(fname,"wt");		// Abre o arquivo inserido pelo usu�rio em modo de escrita
				
					/* Testa se houve erro ao abrir o arquivo */
				if (fp == NULL)		// Checa se o arquivo foi aberto corretamente
				{
					puts(" *Ocorreu um erro ao tentar abrir o arquivo! \n");
			    	puts("   **Encerrando o programa...");
			    	exit(1);		// Encerra o programa indicando um erro
				}
				else
				{
					puts(" *O arquivo foi aberto com sucesso! \n\n");
				}
					/* Testa se houve erro ao abrir o arquivo */
				/* RECEBENDO O ARQUIVO */
				
				/* Cifrando */
				puts("Insira abaixo a mensagem que deseja cifrar! : ");
				scanf("%s",cifrar);
				fflush(stdin);		// Limpando o buffer de entrada
				
				puts("Qual o deslocamento desejado? (S�o aceitos somente valores entre 1-25) :");
				scanf("%d",&rot);
				fflush(stdin);		// Limpando o buffer de entrada
				while( rot < 1 || rot > 25 )		// Caso o valor inserido n�o esteja entre 1 e 25,
				{	// o programa fica mostrando mensagem de erro, at� receber um valor v�lido
					puts("Valor inv�lido! Tente novamente :");
					scanf("%d",&rot);
					fflush(stdin);		// Limpando o buffer de entrada
				}
				
				tamanho = strlen(cifrar);	// Descobre o tamanho da mensagem a ser cifrada
				for(i=0; i<tamanho; i++)	// Percorre todos os caracteres da string 'cifrar'
				{
					cifrar[i] = toupper(cifrar[i]);		// Fazendo com que todas as letras da string sejam mai�sculas
					cifrar[i] = cifrar[i] + rot;		// Cifrando a mensagem a partir do deslocamento desejado
					
					if( cifrar[i] > 'Z' )		// Caso o deslocamento fa�a com que
					{	// o valor seja maior que o caracter Z, retorna para A e soma o valor restante
						result = cifrar[i] - 'Z';
						cifrar[i] = ('A' - 1) + result;
					}
				}
				
				/* Escrevendo resultado */
				fprintf(fp,"%s",cifrar);
				printf("\n *A mensagem foi cifrada e anexada no arquivo %s com sucesso! :) \n\n",fname);
				fclose(fp);		// Fecha o arquivo de escrita
				
				break;
			
			case 2: 	// DECIFRAR UMA MENSAGEM
				/* RECEBENDO O ARQUIVO */
				puts("Digite o nome do arquivo de texto desejado: ");
				gets(fname);
				strcat(fname,".txt");		// Adiciona o texto '.txt' ao final da string 'fname'
				fp=fopen(fname,"rt");		// Abre o arquivo inserido pelo usu�rio em modo de leitura
				
					/* Testa se houve erro ao abrir o arquivo */
				if (fp == NULL)		// Checa se o arquivo foi aberto corretamente
				{
					puts(" *Ocorreu um erro ao tentar abrir o arquivo! \n");
			    	puts("   **Encerrando o programa...");
			    	exit(1);		// Encerra o programa indicando um erro
				}
				else
				{
					puts(" *O arquivo foi aberto com sucesso! \n\n");
				}
					/* Testa se houve erro ao abrir o arquivo */
				/* RECEBENDO O ARQUIVO */
				
				/* Descobrindo quantos caracteres temos no arquivo */
				fseek(fp, 0, SEEK_END);		// Coloca o fluxo na �ltima posi��o do arquivo
				tamanho = ftell(fp);		// 'conta' recebe a quantidade de caracteres no arquivo
				rewind(fp);					// Retorna o fluxo para a primeira posi��o
				fgets(string, tamanho+1, fp);	// Armazena o conte�do do arquivo
				/* Descobrindo quantos caracteres temos no arquivo */
				
				for(i=1; i<26; i++)		// Percorre todos os 25 poss�veis deslocamentos (1-25)
				{
					for(j=0; j<tamanho; j++)		// Percorre todos os caracteres da string 'string'
					{
						aux[j] = string[j] + i;		// Realiza o deslocamento referente � vari�vel 'i'
						// O deslocamento fica armazenado em uma vari�vel de aux�lio
			
						if( aux[j]> 'Z' )		// Caso o deslocamento fa�a com que
						{	// o valor seja maior que o caracter Z, retorna para A e soma o valor restante
							result = aux[j] - 'Z';
							aux[j] = ('A' - 1) + result;
						}
						
			            /* TR�S PRATELEIRAS COM AS LETRAS QUE MAIS APARECEM NA L�NGUA PORTUGUESA */
			
						if( aux[j] == 'A' || aux[j] == 'E' || aux[j] == 'O')
						{
							soma[i-1]+=3;
						}
			
						if( aux[j] == 'S' || aux[j] == 'R' || aux[j] == 'I')
						{
							soma[i-1]+=2;
						}
			
						if( aux[j] == 'N' || aux[j] == 'M' || aux[j] == 'U')
						{
							soma[i-1]++;
						}
			
						/* CADA UMA COM SEU RESPECTIVO PESO CONFORME A FREQU�NCIA QUE APARECEM */
			
					}
					aux[j] = '\0';	// Indica o final da string
			//		printf("%s \t %d \n",aux,soma[i-1]);
				}
				
				for(i=0; i<26; i++)		// Percorre todos os 25 poss�veis deslocamentos (1-25)
				{	// Descobrindo onde est� o maior valor de soma
					if( soma[i] > maior[0] )
					{
						maior[0] = soma[i];	// Armazena o maior valor de soma na primeira posi��o de 'maior'
						desloca[0] = i;		// Armazena na primeira posi��o de 'desloca' qual o deslocamento
						// que causa o maior valor de soma 
					}
				}
				
				for(i=0; i<26; i++)		// Percorre todos os 25 poss�veis deslocamentos (1-25)
				{	// Descobrindo onde est� o segundo maior valor de soma
					if(soma[i] > maior[1] && soma[i] != maior[0] )	
					{
						maior[1] = soma[i];	// Armazena o segundo maior valor de soma na segunda posi��o de 'maior'
						desloca[1] = i;		// Armazena na segunda posi��o de 'desloca' qual o deslocamento
						// que causa o segundo maior valor de soma 
					}
				}
				
				for(i=0; i<tamanho; i++)		// Percorre todos os caracteres da string 'string'
				{
					resp_1[i] = string[i] + desloca[0]+1; 	// Armazena em 'resp_1' o primeiro caso
					// mais prov�vel para ser a mensagem decifrada (Indicado pelo maior valor de soma)
					
					if( resp_1[i] > 'Z' )		// Caso o deslocamento fa�a com que
					{	// o valor seja maior que o caracter Z, retorna para A e soma o valor restante
						result = resp_1[i] - 'Z';
						resp_1[i] = ('A' - 1) + result;
					}
				}
				resp_1[i] = '\0';		// Indica o final da string
				
				for(i=0; i<tamanho; i++)		// Percorre todos os caracteres da string 'string'
				{
					resp_2[i] = string[i] + desloca[1]+1; 	// Armazena em 'resp_2' o segundo caso
					// mais prov�vel para ser a mensagem decifrada (Indicado pelo segundo maior valor de soma)
					
					if( resp_2[i] > 'Z' )		// Caso o deslocamento fa�a com que
					{	// o valor seja maior que o caracter Z, retorna para A e soma o valor restante
						result = resp_2[i] - 'Z';
						resp_2[i] = ('A' - 1) + result;
					}	
				}
				resp_2[i] = '\0';		// Indica o final da string
				
				/* Exibindo para o usu�rio os casos mais prov�veis */
				puts("Esses s�o os dois casos mais prov�veis, qual dos dois est� correto?");
				printf("1. %s \n2. %s \n",resp_1,resp_2);
				printf("\nInsira a op��o desejada: ");		// O usu�rio decide qual o caso correto (1 ou 2)
                scanf("%d",&cntrl);
                fflush(stdin);		// Limpando o buffer de entrada
                while( cntrl < 1 || cntrl > 2 )		// Caso o valor inserido n�o esteja entre 1 e 2,
				{	// o programa fica mostrando mensagem de erro, at� receber um valor v�lido
					puts("Valor inv�lido! Tente novamente :");
					scanf("%d",&cntrl);
					fflush(stdin);		// Limpando o buffer de entrada
				}
				
                fclose(fp);		// Fecha o arquivo de leitura
                
                /* Criando um arquivo que cont�m o resultado */
				tamanho = strlen(fname);	// Armazena a quantidade de caracteres da string 'fname'
				fname[tamanho-4] = '\0';	// Apaga o .txt que fica no final de 'fname'
				strcat(fname,fname2);		// Adiciona o texto "_dec.txt" no final de 'fname'
				fp = fopen(fname,"wt");	// Abre um segundo arquivo em modo de escrita
				
				/* Escrevendo o resultado no arquivo */
                if( cntrl == 1)
                {
                	fprintf(fp,"A frase %s decifrada �: %s", string, resp_1);
				}
				else if( cntrl == 2 )
				{
					fprintf(fp,"A frase %s decifrada �: %s", string, resp_2);
				}
				printf(" *A resposta foi anexada no arquivo %s com sucesso! :) \n\n",fname);
				/* Escrevendo o resultado no arquivo */
				
				for(i=0; i<26; i++)
					soma[i] = 0;		// Zerando a vari�vel 'soma'
				for(i=0; i<2; i++)
				{
					maior[i] = 0;		// Zerando a vari�vel 'maior'
					desloca[i] = 0; 	// Zerando a vari�vel 'desloca'
				}
				
				fclose(fp);		// Fecha o arquivo de escrita
					
				break;
				
			case 3:		// ENCERRAR O PROGRAMA
				exit(0);	// Indica que o programa encerrou sem erros
				break;
		}
		
		// Voltando ao menu de op��es		
		printf("\nAperte qualquer tecla para voltar ao menu! \n");
		system("pause");
		cntrl = menu();
	}
}

int start_m(void)
{
	int cntrl;
	do
	{
		system("cls");
		puts("*!>  TRABALHO DE PROGRAMA��O - A C�sar o que � de C�sar  <!* ");
		puts("\tGuilherme da Cunha Pioner - n� 6");
		puts("\tPedro Stanislau Tomacheski - n� 21");
		puts("\t\t   TURMA 4311 \n");
		puts("Este programa serve tanto para decifrar quanto cifrar uma mensagem ");
		puts("utilizando a famosa Cifra de C�sar. ");
		
		puts("\nDeseja entender como funciona a Cifra de C�sar? ");
		puts("1. Sim");
		puts("2. N�o");
		printf("Insira a op��o desejada: ");
		scanf("%d",&cntrl);
		fflush(stdin);		// Limpando o buffer de entrada
	} while ( cntrl < 1 || cntrl > 2 );		// Caso o valor inserido n�o esteja entre 1 e 2,
	// reapresenta a tela do menu de in�cio e deixa o usu�rio inserir novamente o valor, at�
	// receber um que seja v�lido.
	
	if(cntrl == 1)		// Se o usu�rio desejar aprender mais sobre a cifra de c�sar, imprime
	{	// o texto abaixo para ajudar ele no entendimento:
		puts("\nA Cifra de C�sar (ou cifra de troca, c�digo de C�sar ou troca de C�sar) ");
		puts("� uma das mais simples e famosas t�cnicas de criptografia.");
		puts("O m�todo constitui-se em substituir cada letra do texto por outra, ");
		puts("localizada a uma dist�ncia fixa desta.");
		puts("Por exemplo, em uma troca de tr�s posi��es, o A � substituido por D, ");
		puts("o B por E e assim sucessivamente, como mostrado abaixo: \n");
		puts("Alfabeto Original");
		puts("\t+---+   +---+   +---+   +---+   +---+   +---+   +---+");
		puts("\t| X |   | Y |   | Z |   | A |   | B |   | C |   | D |");
		puts("\t+---+   +---+   +---+   +---+   +---+   +---+   +---+");
		puts("\t  |       |       |       |       |       |       |  ");
		puts("\t   |       |       |       |       |       |       |  ");
		puts("\t   V       V       V       V       V       V       V  ");
		puts("\t +---+   +---+   +---+   +---+   +---+   +---+   +---+");
		puts("\t | A |   | B |   | C |   | D |   | E |   | F |   | G |");
		puts("\t +---+   +---+   +---+   +---+   +---+   +---+   +---+");
		puts("Alfabeto Deslocado \n");
		system("pause");
	}
	cntrl = menu();
	
	return cntrl;
}

int menu(void)
{
	int cntrl;
	do
	{
		system("cls");
		puts("*!>  TRABALHO DE PROGRAMA��O - A C�sar o que � de C�sar  <!* ");
		puts("\tGuilherme da Cunha Pioner - n� 6");
		puts("\tPedro Stanislau Tomacheski - n� 21");
		puts("\t\t   TURMA 4311 \n");
		puts("Este programa serve tanto para decifrar quanto cifrar uma mensagem ");
		puts("utilizando a famosa Cifra de C�sar. ");
	
		puts("\n=+= Op��es Dispon�veis =+=");
		puts("1. Cifrar uma mensagem em C�sar utilizando um arquivo de texto");
		puts("2. Decifrar uma mensagem em C�sar utilizando um arquivo de texto");
		puts("3. Encerrar o programa");
		printf("Insira a op��o desejada: ");
		scanf("%d",&cntrl);
		fflush(stdin);		// Limpando o buffer de entrada
	} while( cntrl < 1 || cntrl > 3 );	// Caso o valor inserido n�o esteja entre 1 e 3,
	// reapresenta a tela do menu e deixa o usu�rio inserir novamente o valor, at�
	// receber um que seja v�lido.
	printf("\n\n");		// Imprime duas novas linhas
	
	return cntrl;
}
