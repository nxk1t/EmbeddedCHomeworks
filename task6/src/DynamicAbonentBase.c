#include "aBaseFunctionality.h"

int main()
{
    int choice, n = 0;
    struct abonent *db;

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
            addAbonent(&db, &n);
            break;

        case 2:
            system("clear");
            deleteAbonent(&db, &n);
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
            if (!n) initAbonent(&db);
            free(db);
            exit(EXIT_SUCCESS);

        default:
            printf("\nТакой опции не существует!\n");
            break;
        }
    }
}