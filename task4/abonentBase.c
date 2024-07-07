#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <stdlib.h>

#define STRUCT_SIZE 100

struct abonent {
    char name[20];
    char second_name[20];
    char tel[20];
};

void initDataBase(struct abonent data[])
{
    for (int i = 0; i < STRUCT_SIZE; i++)
    {
        memset(data[i].name, 0, sizeof(data[i].name));
        memset(data[i].second_name, 0, sizeof(data[i].second_name));
        memset(data[i].tel, 0, sizeof(data[i].tel));
    }
}

int addAbonent(struct abonent data[], int* n)
{
    char name[20] = { 0 }, secondName[20] = { 0 }, phoneNumber[20] = { 0 };

    printf("Введите имя абонента: ");
    scanf("%s", &name);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(name) > 20)
    {
        printf("При попытки записи имени произошла ошибка!\n");
        return 1;
    }

    printf("\nВведите фамилию абонента: ");
    scanf("%s", &secondName);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(secondName) > 20)
    {
        printf("При попытки записи фамилии произошла ошибка!\n");
        return 1;
    }

    printf("\nВведите номер телефона абонента: ");
    scanf("%s", &phoneNumber);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(phoneNumber) > 20)
    {
        printf("При попытки записи номера телефона произошла ошибка!\n");
        return 1;
    }

    if (*n < STRUCT_SIZE)
    {
        strcpy(data[*n].name, name);
        strcpy(data[*n].second_name, secondName);
        strcpy(data[*n].tel, phoneNumber);
        *n = *n + 1;
        printf("\nАбонент был успешно добавлен!");
    }
    else printf("\nБаза абонентов уже заполнена, чтобы добавить нового - удалите существующего\n");

    memset(name, 0, sizeof(name));
    memset(secondName, 0, sizeof(secondName));
    memset(phoneNumber, 0, sizeof(phoneNumber));

    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {}
    printf("\nДля продолжения нажмите любую клавишу...");
    getchar();

    return 0;
}

void printAbonents(struct abonent* data, int n)
{
    printf("Список абонентов:\n");
    if (n == 0) printf("Список абонентов пуст!\n");
    else
    {
        for (int i = 0; i < n; i++)
        {
            printf("%d) ", i + 1);
            printf("%s, ", data[i].name);
            printf("%s, ", data[i].second_name);
            printf("%s\n", data[i].tel);
        }
    }

    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {}
    printf("\nДля продолжения нажмите любую клавишу...");
    getchar();
}

void dataBaseRebuild(struct abonent* data, int n, int deletedIndex)
{
    for (int i = deletedIndex - 1; i < n; i++)
    {
        strcpy(data[i].name, data[i + 1].name);
        strcpy(data[i].second_name, data[i + 1].second_name);
        strcpy(data[i].tel, data[i + 1].tel);
    }
}

void deleteAbonent(struct abonent* data, int* n)
{
    int numToDelete;
    printAbonents(data, *n);

    if (*n != 0) 
    {
        printf("\nВведите номер абонента, которого вы хотите удалить: ");
        scanf("%d", &numToDelete);

        memset(data[numToDelete - 1].name, 0, sizeof(data[numToDelete - 1].name));
        memset(data[numToDelete - 1].second_name, 0, sizeof(data[numToDelete - 1].second_name));
        memset(data[numToDelete - 1].tel, 0, sizeof(data[numToDelete - 1].tel));

        dataBaseRebuild(data, *n, numToDelete);
        *n = *n - 1;

        printf("\nАбонент был успешно удален!");

        int ch;
        while ((ch = getchar()) != EOF && ch != '\n') {}
        printf("\nДля продолжения нажмите любую клавишу...");
        getchar();
    }
}

int searchAbonent(struct abonent* data, int n)
{
    char searchName[20];

    printf("Введите имя абонента: ");
    scanf("%s", &searchName);
    if (strlen(searchName) > 20)
    {
        printf("При попытке ввода имени произошла ошибка!");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        if (!strcmp(searchName, data[i].name))
        {
            printf("%d) ", i + 1);
            printf("%s, ", data[i].name);
            printf("%s, ", data[i].second_name);
            printf("%s\n", data[i].tel);
        }
    }

    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {}
    printf("\nДля продолжения нажмите любую клавишу...");
    getchar();

    return 0;
}

int main()
{
    int choice, n = 0;
    struct abonent db[STRUCT_SIZE];

    initDataBase(db);

    while (1)
    {
        system("clear");
        printf("1) Добавить абонента\n");
        printf("2) Удалить абонента\n");
        printf("3) Поиск абонентов по имени\n");
        printf("4) Вывод всех записей\n");
        printf("5) Выход\n");

        printf("\nВыберите опцию: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("clear");
            addAbonent(db, &n);
            break;

        case 2:
            system("clear");
            deleteAbonent(db, &n);
            break;

        case 3:
            system("clear");
            searchAbonent(db, n);
            break;

        case 4:
            system("clear");
            printAbonents(db, n);
            break;

        case 5:
            printf("\nДо свидания!\n");
            exit(0);

        default:
            printf("\nТакой опции не существует!\n");
            break;
        }
    }
}