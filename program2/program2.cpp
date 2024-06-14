#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <windows.h>

using namespace std;
using namespace System;
using namespace System::IO;

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79


struct z {
	char volyer[20];
	char semey[20];
	char vid[20];
	long vozr;
	long ves;
	char redbook[20];
};
struct sp {
	char semey[20];
	long krasnaya;
	struct sp* sled;
	struct sp* pred;
};

int menu(int);
void ptica(struct z*, int NC);
void semivozr(struct z*, int NC);
void samiy(struct z*, int NC);
void listing(struct z*, int NC, struct sp **spisok);
void poiskps(struct z*, int NC);
void diagram(struct z*, int NC, struct sp **spisok);
void vstavka(struct z*,char* semey, int NC, struct sp **spisok);

void ptica(struct z* rnd, int NC) {
	int i;
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::CursorTop=14;
	for(i=0;i<NC;i++)
	{
		if ( strcmp(rnd[i].semey,"Птицы")==0 && rnd[i].vozr>3)
		{
			Console::CursorLeft=10;
			printf(" Вид: ");
			Console::ForegroundColor=ConsoleColor::Red;
			printf("%-49s \n",rnd[i].vid);
			Console::ForegroundColor=ConsoleColor::White;

		}
	}
	getch();
}

void semivozr(struct z* rnd, int NC) {
	int i, k, flag=0;
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::CursorLeft=10;
	Console::CursorTop=14;
	for (k=0; k<NC; k++)
	{
		for (i=k+1; i<NC; i++)
		{
			if(strcmp(rnd[i].semey, rnd[k].semey)==0 && (rnd[i].vozr == rnd[k].vozr) && (flag == 0))
			{
				flag++;
				printf(" Семейство: ");
				Console::ForegroundColor=ConsoleColor::Red;
				printf("%43s \n",rnd[i].semey);
				Console::ForegroundColor=ConsoleColor::White;
				Console::CursorLeft=10;
				printf(" Виды: ");
				Console::ForegroundColor=ConsoleColor::Red;
				printf("%38s",rnd[i].vid);
				Console::ForegroundColor=ConsoleColor::White;
				printf(", ");
				Console::ForegroundColor=ConsoleColor::Red;
				printf("%s \n", rnd[k].vid);
				Console::ForegroundColor=ConsoleColor::White;
				Console::CursorLeft=10;
				printf(" Возраст: ");
				Console::ForegroundColor=ConsoleColor::Red;
				printf("%45ld ",rnd[i].vozr);
				Console::ForegroundColor=ConsoleColor::White;
				break;
			}

		}
	}
	if (flag==0)
	{
		printf("Совпадений не найдено!");
	}
	getch();
}
void samiy(struct z* rnd, int NC) {
	int i=0; struct z best;
	strcpy(best.vid,rnd[0].vid);
	best.vozr=rnd[0].vozr;
	best.ves=rnd[0].ves;
	for(i=1;i<NC;i++)
		if ((rnd[i].vozr>=best.vozr) && (rnd[i].ves>=best.ves))
			{
			strcpy(best.vid,rnd[i].vid);
			best.vozr=rnd[i].vozr;
			best.ves=rnd[i].ves;
			}
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::CursorLeft=10;
	Console::CursorTop=14;
	printf(" Вид: ");
	Console::ForegroundColor=ConsoleColor::Red;
	printf("%49s ",best.vid);
	Console::CursorLeft=10;
	Console::CursorTop=15;
	Console::ForegroundColor=ConsoleColor::White;
	printf(" Возраст:");
	Console::ForegroundColor=ConsoleColor::Red;
	printf("%34ld", best.vozr);
	Console::ForegroundColor=ConsoleColor::White;
	printf(" лет/год(-а) ");
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf(" Вес:");
	Console::ForegroundColor=ConsoleColor::Red;
	printf("%47ld", best.ves);
	Console::ForegroundColor=ConsoleColor::White;
	printf(" кг ");
	getch();
}

void vstavka(struct z* rnd,char* semey, int NC, struct sp **spisok) //Вставка в список
{ 
	int i;
	struct sp *nov,*nt,*z=0;
	for(nt=*spisok; nt!=0 && strcmp(nt->semey,semey)<0; z=nt, nt=nt->sled);
		if(nt && strcmp(nt->semey,semey)==0) return;
			nov=(struct sp*) malloc(sizeof(struct sp));
			strcpy(nov->semey,semey);
			nov->sled=nt;
			nov->pred=z;
			nov->krasnaya=0;
			for(i=0;i<NC;i++)
				if(strcmp(rnd[i].semey,semey)==0)
					if(strcmp(rnd[i].redbook,"Да") == 0)
						nov->krasnaya++;
					if (!z) *spisok=nov;
					else z->sled=nov;
					if (nt) nt->pred=nov;
					return;
}

void listing(struct z* rnd, int NC, struct sp **spisok)//Формирование списка
{
	int i;
	struct sp *nt,*z;
	Console::BufferHeight=720;
	Console::BufferWidth=1280;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	
	printf("\n Алфавитный список");
	printf("\t\t\t\tОбратный список\n");

	if(!*spisok)
		for(i=0;i<NC;i++)
			vstavka(rnd,rnd[i].semey, NC, spisok);
	for (nt=*spisok; nt; nt = nt->sled)
		printf("\n %-15s %ld", nt->semey, nt->krasnaya);
	
	for(nt=*spisok, z=0; nt; z=nt, nt=nt->sled)
		Console::CursorTop=3;
		for (nt=z, i=0; nt; i++, nt=nt->pred)
		{
		Console::CursorLeft = 48;
		printf("%-15s %ld", nt->semey, nt->krasnaya);
		Console::CursorTop+=1;
		}
		//printf("\n %-10s %ld",nt->semey,nt->vozr);
	
	getch();
}

void poiskps(struct z* rnd, int NC) {
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	int i, vidk=0;
	char search[15];
	printf ("\n Список видов по семейству");
	printf ("\n Введите наименование семейства:");
	Console::CursorLeft++;
	Console::CursorVisible::set(true); 
	SetConsoleCP(1251);
	scanf("%s",search);
	SetConsoleCP(866);
	Console::CursorVisible::set(false);
	printf("\n Вид         Вольер     Возраст       Вес        В красной книге?\n");
	for (i=0;i<NC;i++)
		{
		if(strcmp(rnd[i].semey,search)==0)
			{
				printf("\n %-11s %-11s %-2ld %12ld %16s",rnd[i].vid , rnd[i].volyer,rnd[i].vozr,rnd[i].ves,rnd[i].redbook);
			vidk++;
			}
		}
	if (vidk==0) printf("\n Виды не найдены");
	if (vidk) printf("\n\n Количествово видов данного семейства: %-10d",vidk);
	getch();
	return ;

}
void diagram(struct z* rnd, int NC, struct sp **spisok) {
	struct sp *nt; 
	int len,i,NColor; 
	long sum = 0 ;
	char str1[20];
	char str2[20];
	System::ConsoleColor Color; 
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	for(i=0;i<NC;i++)if(strcmp(rnd[i].redbook,"Да") == 0)
		sum++;
	if(!*spisok)
		for(i=0;i<NC;i++)
			vstavka(rnd,rnd[i].semey, NC, spisok);
	Color=ConsoleColor::Gray;
	NColor=8;
	printf("\n   Семейство       Процент в красной книге\n");
	for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++)
	{
		sprintf(str1,"%s",nt->semey);
		sprintf(str2,"%3.1f%%",(nt->krasnaya*100./sum));
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor=ConsoleColor::Gray;;
		Console::CursorLeft=3; Console::CursorTop=2+i+1;
		printf(str1);
		Console::CursorLeft=20;
		printf("%s",str2);
		Console::BackgroundColor=++Color; NColor++;
		Console::CursorLeft=30;
		for(len=0; len<nt->krasnaya*100/sum; len++) printf(" ");
		if(NColor==14) //выделяем на диаграмму 14 цветов
			{Color=ConsoleColor::Gray; NColor=8;}
	}
	getch();
	return ;
	}

int main(array<System::String ^> ^args) {
	int i,n, NC;
	FILE *in;
	struct z *rnd;
	struct sp *spisok = 0;
	char dan[7][55]={
	"Птицы старше 3 лет                                    ",
	"Виды одного семейства и одного возраста               ",
	"Самый старый и тяжелый вид в зоопарке                 ",
	"Алфавитный список семейств и кол-во в красной книге   ",
	"Поиск по семейству                                    ",
	"Диаграмма. Процентное соотн-ние кол-ва в красной книге",
	"Выход                                                 "
	};
	char BlankLine[ ]= "                                                        ";
	setlocale(LC_ALL,"Russian");
	Console::CursorVisible::set(false);
	Console::BufferHeight=Console::WindowHeight;
	Console::BufferWidth=Console::WindowWidth;
	if((in=fopen("zoo.dat","r"))==NULL) {
		printf("\nФайл zoo.dat не открыт !");
		getch(); exit(1);}
	printf("Тип вольера       Семейство       Вид      Возраст     Вес      В красной книге?\n");
	fscanf(in,"%d",&NC);
	rnd=(struct z*)malloc(NC*sizeof(struct z));
	for(i=0;i<NC;i++)
	fscanf(in,"%s%s%s%ld%ld%s", rnd[i].volyer, rnd[i].semey,
	rnd[i].vid, &rnd[i].vozr, 
	&rnd[i].ves, rnd[i].redbook);
	for(i=0;i<NC;i++){
		printf("\n%-17s %-15s %-10s %-5ld %7ld %12s",
	rnd[i].volyer, rnd[i].semey,
	rnd[i].vid, rnd[i].vozr,
	rnd[i].ves, rnd[i].redbook);}
	getch();
	while(1){
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::Gray;
		Console::Clear();
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::Black;
		Console::CursorLeft=10;
		Console::CursorTop=4;
		printf(BlankLine);
		for(i=0;i<7;i++){
			Console::CursorLeft=10;
			Console::CursorTop=i+5;
			printf(" %s ",dan[i]);}
		Console::CursorLeft=10;
		Console::CursorTop=12;
		printf(BlankLine);
		n=menu(7);
		switch(n) {
			case 1: ptica(rnd, NC); break;
			case 2: semivozr(rnd, NC); break;
			case 3: samiy(rnd, NC); break;
			case 4: listing(rnd, NC, &spisok); break;
			case 5: poiskps(rnd, NC); break;
			case 6: diagram(rnd, NC, &spisok); break;
			case 7: exit(0);}}	
	return 0;}
int menu(int n){
	int y1=0,y2=n-1;
	char c=1;
	char dan[7][55]={
	"Птицы старше 3 лет                                    ",
	"Виды одного семейства и одного возраста               ",
	"Самый старый и тяжелый вид в зоопарке                 ",
	"Алфавитный список семейств и кол-во в красной книге   ",
	"Поиск по семейству                                    ",
	"Диаграмма. Процентное соотн-ние кол-ва в красной книге",
	"Выход                                                 "
	};
	while (c!=ESC){
		switch(c) {
		case DOWN: y2=y1; y1++; break;
		case UP: y2=y1; y1--; break;
		case ENTER: return y1+1;
		case HOME: y2=y1; y1=0;break;
		case END: y2=y1; y1=n-1; break;
		}
	if(y1>n-1){y2=n-1;y1=0;}
	if(y1<0) {y2=0;y1=n-1;}
	Console::ForegroundColor=ConsoleColor::Red;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();}
exit(0);
}