/**
**======================================
** Elementos de Programação
** Professor: Marcos Zuccolotto
** Alunos: Guilherme da Cunha Pioner e Pedro Stanislau Tomacheski
** Turma: 4311
** N°s: 6 e 21
**======================================
*/

/**
**=========================================================================================
** Trabalho Prático - A César o que é de César
** Objetivo: Codificar um decifrador de mensagens utilizando a cifra de Cesar.
**
**=========================================================================================
*/

/*
**=========================================================================================
** Considerações do código:
** 
** O seguinte programa, desenvolvido pelos alunos Guilherme Pioner e Pedro Stanislau da
** turma 4311, consiste em um cifrador e decifrador da famosa Cifra de César. O programa
** contém duas ferramentas claras que podem ser facialmente acessadas pelo menu do mesmo,
** sendo estas:
** -> Cifrador:
** O usuário escolhe um arquivo em que deseja armazenar uma mensagem criptografada, após a
** escolha, ele deve inserir a mensagem que deseja mascarar com a Cifra de César. Nesta 
** opção, o usuário escolhe o deslocamento fixo.
**
** -> Decifrador:
** O usuário escolhe um arquivo .txt com uma mensagem já criptografada. A mensagem deve 
** ser composta apenas por letras maiúsculas e não deve conter espaços.
** Nesta função, o programa indicará as duas respostas mais prováveis e o usuário deve
** escolher a correta. (Para encontrarmos quais as respostas mais prováveis, usamos um
** sistema de pesos paras as letras mais incidentes na língua portuguesa, onde as mais
** comuns têm um peso maior, e as menos comuns têm um peso menor. Quando essas letras
** aparecem, seus pesos são somados à uma soma geral para o deslocamento atual.
** Para descobrir as melhores respostas, basta procurar as mensagens deslocadas com o
** maior valor da soma geral, estas serão as mais prováveis de estarem corretas.)
** A resposta da descriptografia estará em um arquivo .txt cujo nome é igual ao do
** inserido pelo usuário, acrescido do sufixo "_dec".
**
** O programa, além do menu principal, contém um menu de inicialização onde o usuário
** pode selecionar se deseja, ou não, aprender como funciona a Cifra de César.
**
** Fonte para as letras mais incidentes na língua portuguesa:
** http://dicionariosvarios.blogspot.com/2013/07/percentuais-de-frequencia-de-letras-no.html
**=========================================================================================
*/



/* Protótipos */
int menu(void);			// Menu geral com as ferramentas do programa
int start_m(void);		// Menu de inicialização (só aparece no início do programa)

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <string.h>

void main(void)
{
	/* Configurações primárias */
	setlocale(LC_ALL,"portuguese");		// Habilita caracteres da língua portuguesa
	srand(time(NULL));					// Habilita a geração de números randômicos

	/* DECLARANDO AS VARIÁVEIS */
	FILE *fp;				// Cria o ponteiro para arquivos
	char fname	 [50];		// String para o nome do arquivo
	char fname2	 [54] = { '_','d','e','c','.','t','x','t' };	// String para o nome do arquivo a ser criado
	char string	[200];		// String original
	char aux	[200];		// String de auxílio
	char resp_1	[200];		// String para a primeira resposta mais provável 
	char resp_2	[200];		// String para a segunda resposta mais provável
	char cifrar	[200];		// String para a mensagem a ser cifrada
	int desloca[2] = {0};	// Array que armazena os deslocamentos das respostas mais prováveis
	int maior[2]   = {0};	// Array que armazena os maiores valores de 'soma'
	int soma[26]   = {0};	// Array que armazena os pesos de cada deslocamento
	int cntrl 	   =  0;	// Variável de controle para as opções
	int tamanho    =  0;	// Variável para o tamanho das strings
	int rot        =  0;	// Variável que armazena o deslocamento da mensagem a ser cifrada
	int result     =  0;	// Variável para auxílio nos deslocamentos
	int i 		   =  0; 	
	int	j 		   =  0;	// Variáveis de controle para os laços de repetições
	/* DECLARANDO AS VARIÁVEIS */
	
	cntrl = start_m();		// Chama o menu de começo de programa.
	
	while(1)
	{	
		switch(cntrl)
		{
			case 1: 	// CIFRAR UMA MENSAGEM
				/* RECEBENDO O ARQUIVO */
				puts("Digite o nome do arquivo de texto desejado: ");
				gets(fname);
				strcat(fname,".txt");		// Adiciona o texto '.txt' ao final da string 'fname'
				fp=fopen(fname,"wt");		// Abre o arquivo inserido pelo usuário em modo de escrita
				
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
				
				puts("Qual o deslocamento desejado? (São aceitos somente valores entre 1-25) :");
				scanf("%d",&rot);
				fflush(stdin);		// Limpando o buffer de entrada
				while( rot < 1 || rot > 25 )		// Caso o valor inserido não esteja entre 1 e 25,
				{	// o programa fica mostrando mensagem de erro, até receber um valor válido
					puts("Valor inválido! Tente novamente :");
					scanf("%d",&rot);
					fflush(stdin);		// Limpando o buffer de entrada
				}
				
				tamanho = strlen(cifrar);	// Descobre o tamanho da mensagem a ser cifrada
				for(i=0; i<tamanho; i++)	// Percorre todos os caracteres da string 'cifrar'
				{
					cifrar[i] = toupper(cifrar[i]);		// Fazendo com que todas as letras da string sejam maiúsculas
					cifrar[i] = cifrar[i] + rot;		// Cifrando a mensagem a partir do deslocamento desejado
					
					if( cifrar[i] > 'Z' )		// Caso o deslocamento faça com que
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
				fp=fopen(fname,"rt");		// Abre o arquivo inserido pelo usuário em modo de leitura
				
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
				fseek(fp, 0, SEEK_END);		// Coloca o fluxo na última posição do arquivo
				tamanho = ftell(fp);		// 'conta' recebe a quantidade de caracteres no arquivo
				rewind(fp);					// Retorna o fluxo para a primeira posição
				fgets(string, tamanho+1, fp);	// Armazena o conteúdo do arquivo
				/* Descobrindo quantos caracteres temos no arquivo */
				
				for(i=1; i<26; i++)		// Percorre todos os 25 possíveis deslocamentos (1-25)
				{
					for(j=0; j<tamanho; j++)		// Percorre todos os caracteres da string 'string'
					{
						aux[j] = string[j] + i;		// Realiza o deslocamento referente à variável 'i'
						// O deslocamento fica armazenado em uma variável de auxílio
			
						if( aux[j]> 'Z' )		// Caso o deslocamento faça com que
						{	// o valor seja maior que o caracter Z, retorna para A e soma o valor restante
							result = aux[j] - 'Z';
							aux[j] = ('A' - 1) + result;
						}
						
			            /* TRÊS PRATELEIRAS COM AS LETRAS QUE MAIS APARECEM NA LÍNGUA PORTUGUESA */
			
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
			
						/* CADA UMA COM SEU RESPECTIVO PESO CONFORME A FREQUÊNCIA QUE APARECEM */
			
					}
					aux[j] = '\0';	// Indica o final da string
			//		printf("%s \t %d \n",aux,soma[i-1]);
				}
				
				for(i=0; i<26; i++)		// Percorre todos os 25 possíveis deslocamentos (1-25)
				{	// Descobrindo onde está o maior valor de soma
					if( soma[i] > maior[0] )
					{
						maior[0] = soma[i];	// Armazena o maior valor de soma na primeira posição de 'maior'
						desloca[0] = i;		// Armazena na primeira posição de 'desloca' qual o deslocamento
						// que causa o maior valor de soma 
					}
				}
				
				for(i=0; i<26; i++)		// Percorre todos os 25 possíveis deslocamentos (1-25)
				{	// Descobrindo onde está o segundo maior valor de soma
					if(soma[i] > maior[1] && soma[i] != maior[0] )	
					{
						maior[1] = soma[i];	// Armazena o segundo maior valor de soma na segunda posição de 'maior'
						desloca[1] = i;		// Armazena na segunda posição de 'desloca' qual o deslocamento
						// que causa o segundo maior valor de soma 
					}
				}
				
				for(i=0; i<tamanho; i++)		// Percorre todos os caracteres da string 'string'
				{
					resp_1[i] = string[i] + desloca[0]+1; 	// Armazena em 'resp_1' o primeiro caso
					// mais provável para ser a mensagem decifrada (Indicado pelo maior valor de soma)
					
					if( resp_1[i] > 'Z' )		// Caso o deslocamento faça com que
					{	// o valor seja maior que o caracter Z, retorna para A e soma o valor restante
						result = resp_1[i] - 'Z';
						resp_1[i] = ('A' - 1) + result;
					}
				}
				resp_1[i] = '\0';		// Indica o final da string
				
				for(i=0; i<tamanho; i++)		// Percorre todos os caracteres da string 'string'
				{
					resp_2[i] = string[i] + desloca[1]+1; 	// Armazena em 'resp_2' o segundo caso
					// mais provável para ser a mensagem decifrada (Indicado pelo segundo maior valor de soma)
					
					if( resp_2[i] > 'Z' )		// Caso o deslocamento faça com que
					{	// o valor seja maior que o caracter Z, retorna para A e soma o valor restante
						result = resp_2[i] - 'Z';
						resp_2[i] = ('A' - 1) + result;
					}	
				}
				resp_2[i] = '\0';		// Indica o final da string
				
				/* Exibindo para o usuário os casos mais prováveis */
				puts("Esses são os dois casos mais prováveis, qual dos dois está correto?");
				printf("1. %s \n2. %s \n",resp_1,resp_2);
				printf("\nInsira a opção desejada: ");		// O usuário decide qual o caso correto (1 ou 2)
                scanf("%d",&cntrl);
                fflush(stdin);		// Limpando o buffer de entrada
                while( cntrl < 1 || cntrl > 2 )		// Caso o valor inserido não esteja entre 1 e 2,
				{	// o programa fica mostrando mensagem de erro, até receber um valor válido
					puts("Valor inválido! Tente novamente :");
					scanf("%d",&cntrl);
					fflush(stdin);		// Limpando o buffer de entrada
				}
				
                fclose(fp);		// Fecha o arquivo de leitura
                
                /* Criando um arquivo que contém o resultado */
				tamanho = strlen(fname);	// Armazena a quantidade de caracteres da string 'fname'
				fname[tamanho-4] = '\0';	// Apaga o .txt que fica no final de 'fname'
				strcat(fname,fname2);		// Adiciona o texto "_dec.txt" no final de 'fname'
				fp = fopen(fname,"wt");	// Abre um segundo arquivo em modo de escrita
				
				/* Escrevendo o resultado no arquivo */
                if( cntrl == 1)
                {
                	fprintf(fp,"A frase %s decifrada é: %s", string, resp_1);
				}
				else if( cntrl == 2 )
				{
					fprintf(fp,"A frase %s decifrada é: %s", string, resp_2);
				}
				printf(" *A resposta foi anexada no arquivo %s com sucesso! :) \n\n",fname);
				/* Escrevendo o resultado no arquivo */
				
				for(i=0; i<26; i++)
					soma[i] = 0;		// Zerando a variável 'soma'
				for(i=0; i<2; i++)
				{
					maior[i] = 0;		// Zerando a variável 'maior'
					desloca[i] = 0; 	// Zerando a variável 'desloca'
				}
				
				fclose(fp);		// Fecha o arquivo de escrita
					
				break;
				
			case 3:		// ENCERRAR O PROGRAMA
				exit(0);	// Indica que o programa encerrou sem erros
				break;
		}
		
		// Voltando ao menu de opções		
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
		puts("*!>  TRABALHO DE PROGRAMAÇÃO - A César o que é de César  <!* ");
		puts("\tGuilherme da Cunha Pioner - n° 6");
		puts("\tPedro Stanislau Tomacheski - n° 21");
		puts("\t\t   TURMA 4311 \n");
		puts("Este programa serve tanto para decifrar quanto cifrar uma mensagem ");
		puts("utilizando a famosa Cifra de César. ");
		
		puts("\nDeseja entender como funciona a Cifra de César? ");
		puts("1. Sim");
		puts("2. Não");
		printf("Insira a opção desejada: ");
		scanf("%d",&cntrl);
		fflush(stdin);		// Limpando o buffer de entrada
	} while ( cntrl < 1 || cntrl > 2 );		// Caso o valor inserido não esteja entre 1 e 2,
	// reapresenta a tela do menu de início e deixa o usuário inserir novamente o valor, até
	// receber um que seja válido.
	
	if(cntrl == 1)		// Se o usuário desejar aprender mais sobre a cifra de césar, imprime
	{	// o texto abaixo para ajudar ele no entendimento:
		puts("\nA Cifra de César (ou cifra de troca, código de César ou troca de César) ");
		puts("é uma das mais simples e famosas técnicas de criptografia.");
		puts("O método constitui-se em substituir cada letra do texto por outra, ");
		puts("localizada a uma distância fixa desta.");
		puts("Por exemplo, em uma troca de três posições, o A é substituido por D, ");
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
		puts("*!>  TRABALHO DE PROGRAMAÇÃO - A César o que é de César  <!* ");
		puts("\tGuilherme da Cunha Pioner - n° 6");
		puts("\tPedro Stanislau Tomacheski - n° 21");
		puts("\t\t   TURMA 4311 \n");
		puts("Este programa serve tanto para decifrar quanto cifrar uma mensagem ");
		puts("utilizando a famosa Cifra de César. ");
	
		puts("\n=+= Opções Disponíveis =+=");
		puts("1. Cifrar uma mensagem em César utilizando um arquivo de texto");
		puts("2. Decifrar uma mensagem em César utilizando um arquivo de texto");
		puts("3. Encerrar o programa");
		printf("Insira a opção desejada: ");
		scanf("%d",&cntrl);
		fflush(stdin);		// Limpando o buffer de entrada
	} while( cntrl < 1 || cntrl > 3 );	// Caso o valor inserido não esteja entre 1 e 3,
	// reapresenta a tela do menu e deixa o usuário inserir novamente o valor, até
	// receber um que seja válido.
	printf("\n\n");		// Imprime duas novas linhas
	
	return cntrl;
}
