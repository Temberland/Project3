#define _CRT_SECURE_NO_WARNINGS//чтобы не добавлять _s к scanf
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#pragma execution_character_set( "utf-8" )
#include <time.h>
//структура фильма
typedef struct Film {
    char name[50];
    char year[10];
    char country[50];
    char genre[50];
    char rating[10];
} Film;
//структура фильма

//структура элемента списка(нода)
typedef struct Node {
    Film* film;
    struct Node* next;
    struct Node* prev;
} Node;
//структура элемента списка(нода)

//двусвязный список
typedef struct List {
    int size;
    Node* head;
    Node* tail;
} List;
//двусвязный список

//мои функции
List* init_list();//инициализация списка
void pushFront(List* list, Film* film);//добавление элемента в начало
void* popFront(List* list);//удаление элемента с начала
void pushBack(List* list, Film* film);//удаление элемента с конца
Node* getNth(List* list, int index);//получение n-ого элемента
void* deleteNth(List* list, int index);//удаление n-ого элемента(начинается с 0)
void printList(List* list, void (*fun)(Film*));//печать двусвязного списка
void printNode(Film* film);//печать одного элемента


//инициализация списка
List* init_list() {

    List* tmp = (List*)malloc(sizeof(List));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}
//инициализация списка

//добавление элемента в начало
void pushFront(List* list, Film* film) {

    Node* tmp = (Node*)malloc(sizeof(Node));

    if (tmp == NULL) {
        exit(0);
    }

    tmp->film = film;
    tmp->next = list->head;
    tmp->prev = NULL;

    if (list->head) {
        list->head->prev = tmp;
    }

    list->head = tmp;

    if (list->tail == NULL) {
        list->tail = tmp;
    }

    list->size++;

}
//добавление элемента в начало

//удаление элемента с начала
void* popFront(List* list) {

    Node* prev;
    void* tmp;

    if (list->head == NULL) {
        exit(0);
    }

    prev = list->head;
    list->head = list->head->next;

    if (list->head) {
        list->head->prev = NULL;
    }

    if (prev == list->tail) {
        list->tail = NULL;
    }

    tmp = prev->film;

    free(prev);

    list->size--;

    return tmp;
}
//удаление элемента с начала

//удаление элемента с конца
void pushBack(List* list, Film* film) {

    Node* tmp = (Node*)malloc(sizeof(Node));

    if (tmp == NULL) {
        exit(0);
    }

    tmp->film = film;
    tmp->next = NULL;
    tmp->prev = list->tail;

    if (list->tail) {
        list->tail->next = tmp;
    }

    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }

    list->size++;

}
//удаление элемента с конца

//получение n-ого элемента
Node* getNth(List* list, int index) {

    Node* tmp = list->head;
    int i = 0;

    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }

    return tmp;

}
//получение n-ого элемента

//удаление n-ого элемента(начинается с 0)
void* deleteNth(List* list, int index) {

    Node* elm = NULL;
    void* tmp = NULL;

    elm = getNth(list, index);

    if (elm == NULL) {
        exit(5);
    }

    if (elm->prev) {
        elm->prev->next = elm->next;
    }

    if (elm->next) {
        elm->next->prev = elm->prev;
    }

    tmp = elm->film;

    if (!elm->prev) {
        list->head = elm->next;
    }

    if (!elm->next) {
        list->tail = elm->prev;
    }

    free(elm);

    list->size--;

    return tmp;

}
//удаление n-ого элемента(начинается с 0)

//печать двусвязного списка
void printList(List* list, void (*fun)(Film*)) { //указатель на функцию

    Node* tmp = list->head;

    while (tmp) {
        fun(tmp->film);
        tmp = tmp->next;
    }

    printf("\n");

}
//печать двусвязного списка

//печать одного элемента
void printNode(Film* film) { //передаем getNth(list, index)->film->name

    puts(film->name);
    puts(film->year);
    puts(film->country);
    puts(film->genre);
    puts(film->rating);
    puts("\n\n");

}
//печать одного элемента

//добавление элементов из файла в список
//const char *__restrict__ _Filename показывает путь к файлу, пишем через кавычки
void films_to_list(List* list, const char* __restrict__ _Filename) {

    FILE* films = fopen(_Filename, "r");

    Film film[1000]; //максимальное количество строк в файле films.txt
    int count = 0;

    for (int i = 0; !feof(films); i++) { //пока не конец файла, пока указатель не в конце файла

        if (fgets(film[i].name, 50, films) != 0) {
            count++;
        }
    }

    fseek(films, 0, SEEK_SET); //указатель в начало файла

    for (int i = 0; i < count / 5; i++) {

        fgets(film[i].name, 50, films);
        fgets(film[i].year, 10, films);
        fgets(film[i].country, 50, films);
        fgets(film[i].genre, 50, films);
        fgets(film[i].rating, 10, films);

        if (list->size == 0) {
            pushFront(list, &film[i]);
        }

        else {
            pushBack(list, &film[i]);
        }
    }

    fclose(films);

}
//добавление элементов из файла в список

//добавление фильма
void film_add(List* list, const char* __restrict__ _Filename) {

    Film film;
    FILE* films = fopen(_Filename, "a");

    fgets(film.name, 50, stdin);
    fgets(film.year, 10, stdin);
    fgets(film.country, 50, stdin);
    fgets(film.genre, 50, stdin);
    fgets(film.rating, 10, stdin);

    fputs(film.name, films);
    fputs(film.year, films);
    fputs(film.country, films);
    fputs(film.genre, films);
    fputs(film.rating, films);

    fclose(films);

    for (int i = 0; list->head != NULL; i++) {
        popFront(list);
    }

    films_to_list(list, "films.txt");
}
//добавление фильма

//удаление фильма
void film_delete(List* list, const char* __restrict__ _Filename, int index) {

    FILE* films = fopen(_Filename, "r");
    FILE* films_copy = fopen("films_copy.txt", "a");

    char string[50];

    for (int i = 0; !feof(films); i++) {

        for (int j = 0; j < 50; j++) {

            string[j] = ' ';
        }

        fgets(string, 50, films);

        int count = 0;

        for (int j = 0; getNth(list, index)->film->name[j] != '\n'; j++) {
            count++;
        }

        if (memcmp(string, getNth(list, index)->film->name, count - 1) == 0) {

            fgets(string, 50, films);
            fgets(string, 50, films);
            fgets(string, 50, films);
            fgets(string, 50, films);

        }
        else {

            if (i != ((5 * list->size) - 4)) {
                fputs(string, films_copy);
            }
            else {
                puts(" ");
            }
        }
    }

    fclose(films);
    fclose(films_copy);

    for (int i = 0; list->head != NULL; i++) {

        popFront(list);
    }

    films_to_list(list, "films_copy.txt");

    if (index == 0) {
        popFront(list);
    }

    else {
        deleteNth(list, index);
    }

    remove("films.txt");
    rename("films_copy.txt", "films.txt");
}
//удаление фильма


//int main() {
    //List* main_list = init_list(); // Инициализация списка
    //films_to_list(main_list, "films.txt"); // Добавление элементов из файла в список
   //printList(main_list, printNode); // Печать двусвязного списка
    //film_add(main_list, "films.txt"); // Добавление фильма 
    //system("clear");
    //printList(main_list, printNode); // Печать двусвязного списка

    //film_delete(main_list, "films.txt", 1); // Удаление n-ого элемента(начинается с 0)
    //system("clear");
   // printList(main_list, printNode); // Печать двусвязного списка

   // getchar();
   // return 0;
//}




int check_number(char login[100]) {
	int pr1 = 0;//проверка на числа, регистр верхний, регистр нижний
	for (int i = 0; i < strlen(login); i++) {//проверка на числа в логине
		for (int j = 48; j <= 57; j++) {
			if (login[i] == j) {
				pr1 = 1;
			}
		}
	}
	return pr1;
}
int check_regist_a(char login[100]) {
	int pr1 = 0;//проверка на числа, регистр верхний, регистр нижний
	for (int i = 0; i < strlen(login); i++) {//проверка на числа в логине
		for (int j = 97; j <= 122; j++) {
			if (login[i] == j) {
				pr1 = 1;
			}
		}
	}
	return pr1;
}
int check_regist_A(char login[100]) {
	int pr1 = 0;//проверка на числа, регистр верхний, регистр нижний
	for (int i = 0; i < strlen(login); i++) {//проверка на числа в логине
		for (int j = 65; j <= 90; j++) {
			if (login[i] == j) {
				pr1 = 1;
			}
		}
	}
	return pr1;
}
void menu_registration() {
	printf("                                                   ╔═══════════╗     ╔═══════════╗\n");
	printf("                                                   ║Регистрация║     ║Авторизация║\n");
	printf("                                                   ╚═══════════╝     ╚═══════════╝\n");
	printf("                                        Нажмите O для регистрации или P для авторизации\n");
	printf("                                                         На английском                    ");
}
void registration() {
	char login[100];//для логина 
	char password[100];//для пароля
	char number_card[100];//для номера карты
	system("cls");
	printf("Введите логин: ");
	scanf("%s", &login);
	int pr1 = 0, pr2 = 0, pr3 = 0;//проверка на числа, регистр верхний, регистр нижний
	pr1 = check_number(login);
	//printf("%d", pr1);
	while ( ((strlen(login) > 20) || (strlen(login) < 3)) || (pr1==0)) { //проверка на условие для логина
		//printf("%d", pr1);
		printf("Длина логина должна составлять от 3 до 20 символов\n");
		printf("Так же проверьте, чтобы в логине были цифры\n");
		printf("Введите логин заного: ");
		scanf("%s", &login);
		pr1 = check_number(login);
	}
	printf("Введите пароль: ");
	scanf("%s", &password);
	pr1 = check_number(password);//проверка чтобы в пароле блыи цифры
	pr2 = check_regist_A(password);//проверка чтобы был верхний регистр
	pr3 = check_regist_a(password);//проверка, чтобы был нижний регистр
	while (((strlen(password) > 20) || (strlen(password) < 6))||(pr1==0)||(pr2==0)||(pr3==0)) {//проверка на условие для пароля
		printf("Длина пароля должна составлять от 6 до 20 символов\n");
		printf("Также проверьте, чтобы пароль содержал цифры, верхний и нижний регистр\n");
		printf("Введите пароль заного: ");
		scanf("%s", &password);
		pr1 = check_number(password);//проверка чтобы в пароле блыи цифры
		pr2 = check_regist_A(password);//проверка чтобы был верхний регистр
		pr3 = check_regist_a(password);//проверка, чтобы был нижний регистр
	}
	printf("Введите номер карты: ");
	scanf("%s", &number_card);
	while (strlen(number_card) != 16) {//проверка на условие для карты
		printf("Допустимая длина 16\n");
		printf("Введите номер карты заного: ");
		scanf("%s", &number_card);
	}
	FILE* loginandpassword = fopen("users.txt", "a");
	fprintf(loginandpassword, "%s\n", login);
	fprintf(loginandpassword, "%s\n", password);
	fprintf(loginandpassword, "%s\n", number_card);
	fprintf(loginandpassword, "0\n");//список избранного по умолчанию ноль
	fprintf(loginandpassword, "0\n");//админ или нет, тоже по умолчанию ноль
	fclose(loginandpassword);
	system("cls");
	printf("                                                   ╔════════════════════╗\n");
	printf("                                                   ║Регистрация успешна!║\n");
	printf("                                                   ╚════════════════════╝\n");
}
int comparison(char login[100], char checklogin[100]) {
	int p = 1;
	for (int i = 0; i < 100; i++) {
		if (login[i] != checklogin[i]) {
			p = 0;
			break;
		}
	}
	return p;
}
int check_login_and_password(char login[100], char password[100]) {
	FILE* loginandpassword = fopen("users.txt", "r");
	char logincheck[100];//для логина, чтобы проверить правильность логина 
	char passcheck[100];//для пароля, чтобы проверить правильность логина 
	int loginplus = 0, passwordplus = 0; //проверить что все условия выполнены
	while (!feof(loginandpassword)) {
		fscanf(loginandpassword, "%s", logincheck);
		//printf("проверка %s\n", logincheck);
		//printf("логин %s\n", login);
		//printf("пароль %s\n", password);
		if (strcmp(login, logincheck) == 0) {
			loginplus = 1;
			printf("верный логин\n");
		}
		if (strcmp(password, logincheck) == 0) {
			passwordplus = 1;
			printf("верный пароль\n");
		}
	}
	//printf("%d %d", loginplus, passwordplus);
	if ((loginplus == 1) && (passwordplus == 1)) {
		printf("1");
		return 1;
	}
	else
		return 0;
	fclose(loginandpassword);

}

int main(){
	SetConsoleOutputCP(65001);
	menu_registration();
	char manage;
	char login[100];//для логина, чтобы проверить правильность логина 
	char password[100];//для пароля, чтобы проверить правильность логина 
	char number_card[100];//для номера карты
	printf("\n");
	manage = _getch();//чтобы при кнопке был выбор между регистрацией и авторизацией
	//Регистрация
	int indefipass = 0, indefilog = 0;
	if ((manage == 'o') || (manage == 'O')) {
		system("cls");
		registration();
	}
	FILE* loginandpassword = fopen("users.txt", "a");
	Sleep(2000);
	system("cls");
	//авторизация
	menu_registration();
	int check = 0;
	if ((manage == 'p') || (manage == 'P')) {
		system("cls");
		printf("Введите логин: ");
		scanf("%s", &login);
		printf("Введите пароль: ");
		scanf("%s", &password);
		
		while (check != 1) {
			check = check_login_and_password(login, password);
			if (check == 0) {
				printf("Неверный логин или пароль\n");
				printf("Попробуйте снова\n");
				printf("Введите логин: ");
				scanf("%s", &login);
				printf("Введите пароль: ");
				scanf("%s", &password);
			}
			if (check == 1) {
				break;
			}
		}
		printf("Вы успешно авторизовались");
	}
}