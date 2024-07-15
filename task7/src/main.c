#include "calc.h"

int main()
{
    int choice;
    long long int result;
    int ch;

    while (1)
    {
        system("clear");
        printf("1) Сложение\n");
        printf("2) Вычитание\n");
        printf("3) Умножение\n");
        printf("4) Деление\n");
        printf("5) Выход\n");

        printf("\nВыберите опцию: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("clear");
            result = add();
            printf("Результат сложения: %lld", result);

            while ((ch = getchar()) != EOF && ch != '\n') {}
            printf("\nДля продолжения нажмите любую клавишу...");
            getchar();

            break;

        case 2:
            system("clear");
            result = sub();
            printf("Результат вычитания: %lld", result);

            while ((ch = getchar()) != EOF && ch != '\n') {}
            printf("\nДля продолжения нажмите любую клавишу...");
            getchar();
            
            break;

        case 3:
            system("clear");
            result = mul();
            printf("Результат умножения: %lld", result);

            while ((ch = getchar()) != EOF && ch != '\n') {}
            printf("\nДля продолжения нажмите любую клавишу...");
            getchar();

            break;

        case 4:
            system("clear");
            result = division();
            printf("Результат целочисленного деления: %lld", result);

            while ((ch = getchar()) != EOF && ch != '\n') {}
            printf("\nДля продолжения нажмите любую клавишу...");
            getchar();

            break;

        case 5:
            printf("\nДо свидания!\n");
            exit(EXIT_SUCCESS);

        default:
            printf("\nТакой опции не существует!\n");
            while ((ch = getchar()) != EOF && ch != '\n') {}
            break;
        }
    }
    return 0;
}