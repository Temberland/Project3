#define _CRT_SECURE_NO_WARNINGS//чтобы не добавлять _s к scanf
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#pragma execution_character_set( "utf-8" )
#include <time.h>

//char display() {
	//char a[100];
	//printf("Введите логин: ");
	//scanf("%s", a);
//}
int main() {
	SetConsoleOutputCP(65001);

	printf("                                                   ╔═══════════╗     ╔═══════════╗\n");
	printf("                                                   ║Регистрация║     ║Авторизация║\n");
	printf("                                                   ╚═══════════╝     ╚═══════════╝\n");
	printf("                                        Нажмите O для регистрации или P для авторизации\n");
	char a;
	char login[100];
	char password[100];
	a = _getch();
	//printf("%c", a);
}