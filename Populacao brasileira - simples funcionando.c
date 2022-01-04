/* Investigar o crescimento usando dados de 2010 à 2019.
E fazer um programa que prevê a população brasileira em 20 anos.
(regressão linear) y´=ax´+b | a=E 
Fonte: ftp://ftp.ibge.gov.br/Estimativas_de_Populacao/Estimativas_2013/serie_2001_2013_TCU.pdf
Demais anos conforme matérias que citam IBGE como fonte
Valores da população (P) foram considerados na notação P * 10^6
*/

#include <stdio.h>
#include <math.h>
#include <time.h>

float coefcorrel (int x[], double y[], int n, FILE *arqresults); //função para calculo do coeficiente de correlação
float calc_a (int x[], double y[], int n);//função para calculo de a
float calc_b (int x[], double y[], int n, float a);//função para calculo de a

int main ()
{
	int n=20,i=0, x[20], ano;
	float r=0,a=0,b=0;
	double y[20];
	struct tm *data_hora_atual;  
	FILE *seriepopul, *arqresults;
	seriepopul = fopen ("Populacao.txt","r"); // leitura do arquivo de entrada
	arqresults = fopen ("Resultados.txt","w"); //criação do arquivo de saída
	if (seriepopul==NULL || arqresults==NULL)
	{
		printf ("\nErro na abertura do arquivo.\n Certifique-se que o arquivo Populacao.txt esta na mesma pasta que este programa\n\n");
		return 0;
	}
	do //Ler os dados do arquivo em xi e yi
	{
		fscanf (seriepopul,"%d %lf",&x[i],&y[i]);				
		i++;
	}
	while (!feof(seriepopul));	
	r=coefcorrel(x,y,n,arqresults);
	printf ("\nCoeficiente de correlacao: %.2f \n\n",r);
	fprintf (arqresults,"Coeficiente de correlacao: %.2f \n",r);
	a=calc_a(x,y,n);
	b=calc_b(x,y,n,a);
	if (b>0)
	{	
		printf ("Equacao da reta de regressao: y=%.2fx+%.2f\n",a,b);
		fprintf (arqresults,"Equacao da reta de regressao: y=%.2fx+%.2f\n",a,b);
	}
	else 
	{
		printf ("Equacao da reta de regressao: y=%.2fx%.2f\n",a,b);
		fprintf (arqresults,"Equacao da reta de regressao: y=%.2fx%.2f\n",a,b);
	}
	time_t segundos;
	time(&segundos);  
	data_hora_atual = localtime(&segundos); 
	printf ("\nDigite o valor para quantidade de anos que deseja visualisar a projecao da populacao: ");
	scanf ("%d",&ano);
	ano=data_hora_atual->tm_year+1900+ano; //define para qual ano será a projeção	
	printf ("\nA estimativa da populacao em %d = %d \n\n",ano,(a*ano)+b);
	fprintf (arqresults,"\nA estimativa da populacao em %d = %d\n\n",ano,(a*ano)+b);
	fclose (seriepopul);
	fclose (arqresults);
	return 0;	
}
float coefcorrel(int x[], double y[], int n, FILE *arqresults) //função para calculo do coeficiente de correlação
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
	fprintf (arqresults,"Somatorio xi= %d\nSomatorio yi= %lf\nSomatorio xi*yi= %lf\nSomatorio x^2= %d\nSomatorio y^2= %lf\n",somax,somay,somaxy,somax2,somay2);
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
float calc_b (int x[], double y[], int n, float a)
{
	double somay=0;
	int i=0,somax=0;
	float b;
	for (i=0;i<n;i++)
	{
		somax+=x[i];
		somay+=y[i];
	}	
	b=(somay/n)-(a*(somax/n));
	return b;
}
