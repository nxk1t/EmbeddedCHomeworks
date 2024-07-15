#include "aBaseFunctionality.h"

void initAbonent(struct abonent **data)
{
    *data = malloc(sizeof(struct abonent));
}

int addAbonent(struct abonent **data, int* n)
{
    char name[20] = { 0 }, secondName[20] = { 0 }, phoneNumber[20] = { 0 };

    printf("Введите имя абонента: ");
    scanf("%s", name);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(name) > 20)
    {
        printf("При попытки записи имени произошла ошибка!\n");
        return 1;
    }

    printf("\nВведите фамилию абонента: ");
    scanf("%s", secondName);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(secondName) > 20)
    {
        printf("При попытки записи фамилии произошла ошибка!\n");
        return 1;
    }

    printf("\nВведите номер телефона абонента: ");
    scanf("%s", phoneNumber);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(phoneNumber) > 20)
    {
        printf("При попытки записи номера телефона произошла ошибка!\n");
        return 1;
    }

    if (*n < STRUCT_SIZE)
    {
        if (*n == 0) *data = malloc((*n + 1) * sizeof(struct abonent));
        else *data = realloc(*data, (*n + 1) * sizeof(struct abonent));
        strcpy((*data)[*n].name, name);
        strcpy((*data)[*n].second_name, secondName);
        strcpy((*data)[*n].tel, phoneNumber);
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

void dataBaseRebuild(struct abonent** data, int n, int deletedIndex)
{
    for (int i = deletedIndex - 1; i < n; i++)
    {
        strcpy((*data)[i].name, (*data)[i + 1].name);
        strcpy((*data)[i].second_name, (*data)[i + 1].second_name);
        strcpy((*data)[i].tel, (*data)[i + 1].tel);
    }
    *data = realloc(*data, (n - 1) * sizeof(struct abonent));
}

void deleteAbonent(struct abonent** data, int* n)
{
    int numToDelete;
    printAbonents(*data, *n);

    if (*n != 0) 
    {
        printf("\nВведите номер абонента, которого вы хотите удалить: ");
        scanf("%d", &numToDelete);

        if ((numToDelete > *n) || (numToDelete < 1)) printf("Такого абонента не существует!\n");
        else
        {
            memset((*data)[numToDelete - 1].name, 0, sizeof((*data)[numToDelete - 1].name));
            memset((*data)[numToDelete - 1].second_name, 0, sizeof((*data)[numToDelete - 1].second_name));
            memset((*data)[numToDelete - 1].tel, 0, sizeof((*data)[numToDelete - 1].tel));

            dataBaseRebuild(data, *n, numToDelete);
            *n = *n - 1;

            printf("\nАбонент был успешно удален!");
        }

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
    scanf("%s", searchName);
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
