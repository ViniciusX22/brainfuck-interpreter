#include <stdio.h>
#include <windows.h>
#include <locale.h>

#define PI 3.14159265359
#define limpa "cls"
#define LIMPA system("cls");
#define space 32
#define enter 13
#define tab 9
#define pause system("pause");
#define pnull "pause>null"
#define INICIO system(limpa);
#define INICIOT(T) system(limpa);system(T);
#define FIM printf("\n");system(pause);main();
#define delta 127

#define ponta_s_direita 191
#define ponta_s_esquerda 218
#define ponta_i_direita 217
#define ponta_i_esquerda 192
#define horizontal 196
#define vertical 179

#ifdef _conio_c_

void Gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#else

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#endif
void square(int x, int y, int width, int height){
	int i;
	setlocale(0,"C");
	gotoxy(x,y);
	printf("%c",ponta_s_esquerda);
	for(i=0;i<=width;i++){
		printf("%c",horizontal);
	}
	printf("%c",ponta_s_direita);
	for(i=y;i<=height+y;i++){
		gotoxy(x,i+1);
		printf("%c",vertical);
		gotoxy(x+width+2,i+1);
		printf("%c",vertical);
	}
	gotoxy(x,y+height+1);
	printf("%c",ponta_i_esquerda);
	gotoxy(x+1,y+height+1);
	for(i=0;i<=width;i++){
		printf("%c",horizontal);
	}
	gotoxy(x+width+2,y+height+1);
	printf("%c",ponta_i_direita);
	gotoxy(0,0);
	setlocale(0,"");
}

void IntNumerop(int c, int f){
	while(c<=f){
		if (c==1)printf("%d não é primo\n",c);
		else{
			if (c==2 || c==3 || c==5 || c==7 || c==11)printf("%d é primo.\n",c);
			else{
				if (c%2==0 || c%3==0 || c%5==0 || c%7==0 || c%11==0)printf("%d não é primo.\n",c);
				else{
					printf("%d é primo\n",c);
				}
			}
		}
		c++;
	}
}

int Numerop(int num){
	if (num==1)return 0;
	else{
		if (num==2 || num==3 || num==5 || num==7 || num==11)return 1;
		else{
			if (num%2==0 || num%3==0 || num%5==0 || num%7==0 || num%11==0)return 0;
			else{
				return 1;
			}
		}
	}
}

int Max(int a, int b, int c){
	if (a>b && a>c)return a;
	else{
		if (b>a && b>c)return b;
		else{
			if (c>a && c>b || a==c && a==b)return c;
		}
	}
}

char inputc(const char str[]){
	char c;
	printf("%s",str);
	scanf("%c",&c);
	return c;
}

int inputi(const char str[]){
	int c;
	printf("%s",str);
	scanf("%d",&c);
	return c;
}

float inputf(const char str[]){
	float c;
	printf("%s",str);
	scanf("%f",&c);
	return c;
}

double inputd(const char str[]){
	double c;
	printf("%s",str);
	scanf("%lf",&c);
	return c;
}

int Min(int a, int b, int c){
	if (a<b && a<c)return a;
	else{
		if (b<a && b<c)return b;
		else{
			if (c<a && c<b || a==c && a==b)return c;
		}
	}
}
