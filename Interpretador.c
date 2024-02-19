#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <conio.c>
#include <vini.h>

#define CAM "\\Brainfuck_codigos\\"
#define EXT ".brf"

int ptr;
int array[40];
int pont[40];

int xa[40],ya[40],xp[40],yp[40];
int xs,ys;
char loop_inicio,loop_final;

int interpret(char c);
int Novo(void);
int Abrir(void);
void desenha(void);
void atualiza(void);


int main (void){
	int op=0,a=0;
	inicio:
	if(a==1)return 0;
	system("title Interpretador Brainfuck");
	LIMPA
	setlocale(0,"");
	printf("\t\t\tInterpretador Brainfuck");
	printf("\n\nSelecione a opção desejada:");
	printf("\n1 - Criar");
	printf("\n2 - Interpretar");
	printf("\n3 - Sair");
	gotoxy(28,2);
	scanf("%d",&op);
	
	switch(op){
		case 1:
			a = Novo();
			break;
		case 2:
			a = Abrir();
			break;
		case 3:
			break;
		default:
			LIMPA
			printf("\a\n\n\tOpção não encontrada!");
			Sleep(2000);
			goto inicio;
	}
	if(op!=3)goto inicio;
}

int Novo(void){
	char nome[301],c,string,texto[10000],dir[255];
	int i,a,x,y,teste;
	FILE *fp;
	LIMPA
	GetCurrentDirectory(255,dir);
	strcat(dir,CAM);
	printf("Digite o nome do arquivo:");
	fflush(stdin);
	gets(nome);
	strcat(dir,nome);
	strcat(dir,EXT);
	fp = fopen(dir,"w+");
	if(!fp){
		printf("Erro na criação do arquivo!");
		Sleep(2000);
		return 1;
		
	}
	LIMPA
	printf("Texto a ser gravado no arquivo:\n\n");
	strcpy(texto,editor(32,0,500,"",'\0')); //Leitura do texto que será gravado no arquivo
	fim_novo:    // Label Desnecessária (não sei porque ainda está aqui)
	fprintf(fp,"%s",texto);
	fclose(fp);
	return 0;
}


int Abrir(void){
	char nome[301],c,string,texto[10000],dir[255],titulo[100];
	int i,x,y,teste=0,time = 1000;
	int li,lf,a=0;
	FILE *fp;
	LIMPA
	GetCurrentDirectory(255,dir);
	strcat(dir,CAM);
	printf("Digite o nome do arquivo:");
	fflush(stdin);
	gets(nome);
	strcpy(titulo,"title ");
	strcat(titulo,nome);
	system(titulo);
	strcat(dir,nome);
	strcat(dir,EXT);
	fp = fopen(dir,"r+");
	if(!fp){
		printf("Erro na abertura do arquivo! Tente verificar o nome.");
		Sleep(2000);
		return 1;
	}
	LIMPA
	desenha();
	i=0;
	x=0;
	y=14;
	
	// Definição da velocidade
	
	while(c!=enter){
		gotoxy(0,13);
		puts("\t\t\t+ -> Aumentar");
		printf("Velocidade:%d       <enter> -> Continuar",1100 - time);
		puts("\n\t\t\t- -> Diminuir");
		c = getch();
		switch(c){
			case '+':
				if(time>100)
					time -= 100;
				break;
			case '-':
				if(time<1000)
					time += 100;
				break;
		}
		clearLine(13);
		clearLine(14);
		clearLine(15);
	}
	while((c = getc(fp) ) != EOF){ /* Enquanto não chegar ao final do arquivo */
		setlocale(0,"");
		gotoxy(x,y);
		printf("%c", c); /* imprime o caracter lido */
		texto[i] = c;
		i++;
		x++;
		if(x==78){
			y++;
			x=0;
		}
	}
	texto[i] = '\0';
	for(x=0,y=14,i=0;i<strlen(texto);i++,x++){
		teste = interpret(texto[i]);
		if(teste==1){
			return 0;
		}
		gotoxy(x,y);
		textcolor(BLACK);
		textbackground(WHITE);
		printf("%c",texto[i]);
		textcolor(LIGHTGRAY);
		textbackground(BLACK);
		atualiza();
		Sleep(time);
		gotoxy(x,y);
		printf("%c",texto[i]);
		if(loop_inicio == texto[i]){
			li = i;	
			a++;
		}
		if(loop_final == texto[i]){
			lf = i;
			a++;
		}
		if(a==2){
			a = 0;
			while(array[ptr] > 0){
				for(i=li+1,x=i;i<=lf;i++,x++){
					teste = interpret(texto[i]);			
					if(teste==1){
						return 0;
					}
					gotoxy(x,y);
					textcolor(BLACK);
					textbackground(WHITE);
					printf("%c",texto[i]);
					textcolor(LIGHTGRAY);
					textbackground(BLACK);
					atualiza();
					Sleep(time);
					gotoxy(x,y);
					printf("%c",texto[i]);
				}
			}
			x--;
			i--;
		}
		if(x==78){
			y++;
			x=0;
		}
	}
	gotoxy(0,22);
	pause
}

int interpret(char c){
	switch(c){
		case '>':
			if(ptr<38){
				pont[ptr] = 32;
				ptr++;
				pont[ptr] = 24;	
			}else{
				gotoxy(25,18);
				setlocale(0,"");
				printf("Erro na memória!");
				Sleep(2000);
				getch();
				return 1;
			}
			break;
		case '<':
			if(ptr>0){
				pont[ptr] = 32;
				ptr--;
				pont[ptr] = 24;	
			}else{
				gotoxy(25,18);
				setlocale(0,"");
				printf("Erro na memória!");
				Sleep(2000);
				getch();
				return 1;
			}
			break;
		case '+':
			if(array[ptr]<255)
				array[ptr]++;
			else
				array[ptr] = 0;
			break;
		case '-':
			if(array[ptr]>0)
				array[ptr]--;
			else
				array[ptr] = 255;
			break;
		case '.':
			gotoxy(xs,ys);
			putchar(array[ptr]);
			xs++;
			break;
		case ',':
			gotoxy(0,18);
			setlocale(0,"");
			printf("Entrada do usuário:");
			fflush(stdin);
			c = getche();
			array[ptr] = (int)c;
			setlocale(0,"C");
			break;
		case '[':
			loop_inicio = c;
			break;
		case ']':
			loop_final = c;
			break;
	}
	return 0;
}

void desenha(void){
	int x,y,a,i;
	
	setlocale(0,"C");
	//primeira parte
	
	square(0,0,3,1);
	for(x=4,y=0;x<70;x+=4){						  //
		squarem(x,y,3,1,":::1",horizontal_baixo); //
	}											  // Primeira
	squarem(x,y,3,1,":::1",horizontal_baixo);     // Linha
												  //
	for(x=4,y=2;x<74;x+=4){						  //
		drawIn(x,y,horizontal_cima);
	}
	
	square(0,4,3,1);
	for(x=4,y=4;x<70;x+=4){						  //
		squarem(x,y,3,1,":::1",horizontal_baixo); //
	}											  // Segunda
	squarem(x,y,3,1,":::1",horizontal_baixo);     // Linha
												  //
	for(x=4,y=6;x<74;x+=4){						  //
		drawIn(x,y,horizontal_cima);
	}
	
	//Saida
	
	setlocale(0,"");
	gotoxy(0,10);
	printf("Saída:");
	square(6,9,69,1);
	
	xs = 7;
	ys = 10;
	
	//Definição das posições dos arrays na tela
	
	for(i=0,x=1,y=1;i<19;i++,x+=4){
		xa[i] = x;					
		ya[i] = y;					// Segunda
		xp[i] = x+1;				// Linha
		yp[i] = y+2;
	}
	
	for(i=i,x=1,y=5;i<38;i++,x+=4){
		xa[i] = x;					
		ya[i] = y;					// Segunda
		xp[i] = x+1;				// Linha
		yp[i] = y+2;
	}
	
	for(i=0;i<38;i++){	//
		array[i] = 0;	//
		pont[i] = 32;	// Difinição dos valores iniciais do array dos carácters
	}					// e do array da seta
	pont[0] = 24;		// 
	ptr = 0;			//
	
	//Impressão dos valores do array principal e do ponteiro na tela
	
	for(i=0;i<38;i++){
		gotoxy(xa[i],ya[i]);
		printf("%d",array[i]);
		gotoxy(xp[i],yp[i]);
		printf("%c",pont[i]);
	}
	
}

void atualiza(void){
	int i;
	setlocale(0,"C");
	
	//Impressão dos valores do array principal e do ponteiro na tela
	
	for(i=0;i<38;i++){
		gotoxy(xa[i],ya[i]);
		printf("   ",array[i]);
		gotoxy(xa[i],ya[i]);
		printf("%d",array[i]);
		gotoxy(xp[i],yp[i]);
		printf("%c",pont[i]);
	}
	
	setlocale(0,"");
}

