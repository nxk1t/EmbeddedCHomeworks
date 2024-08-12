#include "shop.h"

extern pthread_mutex_t mutex[SHOP_SIZE];
extern long long int shops[SHOP_SIZE], clients_data[CLIENT_SIZE];
int busyShop[SHOP_SIZE] = {0, 0, 0, 0, 0};

//  Функция void* shopVisit(void* data):
//  аргумент void* data - номер потока-клиента, посещаемого магазин;
//  функция не возвращает ничего осмысленного
//  (только 0 для корректной работы) программы.
//  Функция shopVisit содержит логику программы:
//  выбирается свободный магазин, его статус меняется на занятый
//  при помощи массива busyShop. Значение потребности clients_data[*number]
//  уменьшается на значение баланса магазина shops[i].
void* shopVisit(void* data)
{
    int* number = (int*) data;

    while (clients_data[*number] > 0)
    {
        for (int i = 0; i < SHOP_SIZE; i++)
        {
            if (busyShop[i] == 0 && shops[i] != 0)
            {
                pthread_mutex_lock(&mutex[*number]);
                busyShop[i] = 1;

                printf("Я %d покупатель, зашел в %d магазин, там было: %lld, мне необходимо: %lld\n", *number + 1, i + 1, shops[i], clients_data[*number]);

                if (clients_data[*number] < shops[i])
                {
                    shops[i] -= clients_data[*number];
                    clients_data[*number] = 0;
                }
                else
                {
                    clients_data[*number] -= shops[i];
                    shops[i] = 0;
                }

                busyShop[i] = 0;
                pthread_mutex_unlock(&mutex[*number]);

                if (clients_data[*number] <= 0)
                {
                    printf("Я %d покупатель и я закрыл свою потребность\n", *number + 1);
                    pthread_exit(0);
                }
                break;
            }
        }
        sleep(2);
    }
    return 0;
}

//  Функция void* loadShop(void* data):
//  Не содержит аргументов, которые применимы в функции
//  функция не возвращает ничего осмысленного
//  (только 0 для корректной работы) программы.
//
//  В функции loadShop реализован погрузчик:
//  Он заходит в первый свободный магазин и пополняет его баланс на 5000,
//  блокируя магазин для потоков
void* loadShop(void* data)
{
    int stopLoadFlag = 0;
    while (!stopLoadFlag)
    {
        if (clients_data[0] == 0 && clients_data[1] == 0 && clients_data[2] == 0)
        {
            pthread_exit(0);
        }
        else
        {
            for (int i = 0; i < SHOP_SIZE; i++)
            {
                if (busyShop[i] == 0)
                {
                    pthread_mutex_lock(&mutex[3]);
                    busyShop[i] = 1;

                    printf("Я грузчик, зашел в %d магазин, там было: %lld\n", i + 1, shops[i]);

                    shops[i] += 5000;

                    busyShop[i] = 0;
                    pthread_mutex_unlock(&mutex[3]);
                    break;
                }
            }
        }
        sleep(1);
    }
    return 0;
}