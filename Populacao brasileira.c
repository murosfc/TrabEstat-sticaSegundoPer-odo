/*  Investigar o crescimento usando dados de 2010 à 2019.
E fazer um programa que prevê a população brasileira em 20 anos.
(regressão linear) y´=ax´+b | a=E 
*/

#include <stdio.h>
#include <math.h>
#include <time.h>

float coefcorrel (int x[], double y[], int n); //função para calculo do coeficiente de correlação
float calc_a (int x[], double y[], int n);//função para calculo de a

int main ()
{
	int n=0,i=0,option,ano, proj;
	float r=0,a=0,b=0;
	double somay2=0, somaxy=0, somay=0;
	long int somax2=0,somax=0;
	char linha [15]; // variÃ¡vel para contar linhas do arquivo
	struct tm *data_hora_atual; 
	time_t segundos;
	FILE *seriepopul, *arqresults;
	seriepopul = fopen ("Populacao.txt","r"); // leitura do arquivo de entrada
	arqresults = fopen ("Resultados.txt","w"); //criação do arquivo de saÃ­da
	if (seriepopul==NULL || arqresults==NULL)
	{
		printf ("\nErro na abertura do arquivo.\n Certifique-se que o arquivo Populacao.txt esta na mesma pasta que este programa\n\n");
		return 0;
	}
	printf ("*****************************************************************\n");
	printf ("*                                                               *\n");
	printf ("*  BEM VINDO AO PROGRAMA PARA PROJECAO DA POPULACAO BRASILEIRA  *\n");
	printf ("*              UTILIZANDO REGRESSAO LINEAR                      *\n");
	printf ("*                                                               *\n");
	printf ("*****************************************************************\n");	
	while(fgets(linha, sizeof(linha), seriepopul) != NULL) //Loop para contar linhas do arquivo, isso garante funcionamento no futuro com adição de novos dados.
	{    	
        n++;
    }
    n=(int) (n+1)/2; // o contador conta espaço como linha, fórmula para ajustar o resultado
	rewind (seriepopul); // colocar o cursor no inicio do arquivo	
	int x[n];
	double y[n];
	do //Ler os dados do arquivo em xi e yi e calcular as variÃ¡veis auxiliares
	{
		fscanf (seriepopul,"%d %lf",&x[i],&y[i]);					
		i++;		
	}
	while (!feof(seriepopul));	
	for (i=0;i<n;i++)
	{
			somax+=x[i];
			somay+=y[i];
			somaxy+=(x[i]*y[i]);
			somax2+=x[i]*x[i];
			somay2+=y[i]*y[i];
	}
	r=coefcorrel(x,y,n); //chamada da função para cÃ¡lculo do coeficiente de correlação
	a=calc_a(x,y,n); //chamada da função para cÃ¡lculo de a
	b=(somay/n)-(a*(somax/n));	
	time(&segundos); //para calculo do ano atual 
	data_hora_atual = localtime(&segundos); //para calculo do ano atual
	printf ("\nDados de x[i] e y[i] recebidos com sucesso!\n");
	printf ("\nDigite o valor para quantidade de anos que deseja visualisar a projecao da populacao. ");
	printf ("\nA partir do ano atual (%d)+ ",(data_hora_atual->tm_year+1900));
	scanf ("%d",&ano);
	ano=data_hora_atual->tm_year+1900+ano; //define para qual ano serÃ¡ a projeção		
	proj =a*ano+b;	
	printf ("\nCalculos realizados com sucesso!\n\n");
	do
	{
		printf ("\nDigite uma opcao do menu:\n1- Exibir o coeficiente de correlacao;\n");
		printf ("2- Exibir a equacao da reta de regressao;\n3- Exibir projecao da populacao brasileira;\n");
		printf ("4- Exibir variaveis auxiliares (somatorios);\n5- Sair e imprimir valores em arquivo de saida.\n");	
		scanf ("%d",&option);
		system ("clear");
		switch (option)
		{
			case 1:	
            system ("cls");
			printf ("\nCoeficiente de correlacao: %.2f \n",r);
			if (r>0.9)
				printf("Os dados apresentam forte correlacao positiva\n");
			getchar();
			break;
			case 2:	
			system ("cls");			
			if (b>=0)	
				printf ("Equacao da reta de regressao: y= %.2fx + %.2f\n",a,b);
			else 
				printf ("Equacao da reta de regressao: y= %.2fx %.2f\n",a,b);
			getchar();
			break;
			case 3:	
			system ("cls");				
			printf ("\nA estimativa da populacao em %d = %d \n\n",ano,proj);
			getchar();
			break;
			case 4:	
			system ("cls");			
			printf ("Soma x[i]= %d\nSoma x[i]^2= %d\n",somax,somax2);
			printf ("Soma y[i]= %.lf\nSoma y[i]^2= %.lf\n",somay,somay2);
			printf ("Soma x[i]*y[i]= %.lf\n",somaxy);
			printf ("Media x= %d\nMedia y= %.lf\n",somax/n,somay/n);
			getchar();
			break;
			case 5:					
			fprintf (arqresults,"\nCoeficiente de correlacao: %.2f\n",r);
			if (r>0.9)
				fprintf(arqresults,"Os dados apresentam forte correlacao positiva\n");
			if (b>0)			
				fprintf (arqresults,"Equacao da reta de regressao: y=%.2fx+%.2f\n",a,b);
			else 
			fprintf (arqresults,"Equacao da reta de regressao: y=%.2fx%.2f\n",a,b);			
			fprintf (arqresults,"\nA estimativa da populacao em %d = %d \n\n",ano, proj);			
			fprintf (arqresults,"Soma x[i]= %d\nSoma x[i]^2= %d\nSoma y[i]= %.lf\nSoma y[i]^2= %.lf\nSoma x[i]*y[i]= %.lf\n",somax,somax2,somay,somay2,somaxy);
			fprintf (arqresults,"Media x= %d\nMedia y= %.lf\n",somax/n,somay/n);
			system ("cls");
			printf ("\nObrigado por utilizar este programa\n\n");
			fclose (seriepopul);
			fclose (arqresults);
			return 0;
			break;
		}
	}
	while (option !=5);		
}
float coefcorrel(int x[], double y[], int n) //função para calculo do coeficiente de correlação
{
	long int somax2=0,somax=0;
	double somay2=0, somaxy=0, somay=0;
	int i=0;	
	float r=0;
	for (i=0;i<n;i++)
	{
		somax+=x[i];
		somay+=y[i];
		somaxy=somaxy+(x[i]*y[i]);
		somax2+=x[i]*x[i];
		somay2+=y[i]*y[i];		
	}	
	r=(n*somaxy-(somax*somay))/((sqrt(n*somax2-(somax*somax)))*(sqrt(n*somay2-(somay*somay))));
	return r;
}
float calc_a (int x[], double y[], int n)
{
	long int somax2=0,somax=0;
	double somaxy=0, somay=0;
	int i=0;
	float a;
	for (i=0;i<n;i++)
	{
		somax+=x[i];
		somay+=y[i];
		somaxy+=x[i]*y[i];
		somax2+=x[i]*x[i];
	}
	a=(n*somaxy-(somax*somay))/(n*somax2-(somax*somax));
	return a;
}