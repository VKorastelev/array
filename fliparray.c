/** Переворачивание массива из N элементов 
 * @file fliparray.c
 * @author VKorastelev
 * 
 * @detailed Пользователь вводит количество элементов массива.
 Массив заполняется числами от 1 и переворачивается.
 *  
 */

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <malloc.h>

int main() {

    setlocale(LC_ALL, "ru_RU.utf8");

    bool error = false;
    // Одномерный массив
    int *array = NULL;
    int array_size = 0;

    puts("Введите размер N массива (целое положительное число в диапазоне от 1 до 100): ");

    while (scanf("%d", &array_size) != 1 || (array_size < 1 || array_size > 100))
    {
        int ch_trash;
        do
        {
            ch_trash = getchar();
        } while ('\n' != ch_trash && EOF != ch_trash);

        if (EOF == ch_trash)
        {
            error = true;
            puts("Ввод из stdin прекращен (ввели EOF)");
            goto finally;
        }
        puts("Ошибка! Введите целое положительное число N в диапазоне от 1 до 100: ");
    }

    printf("Количество элементов массива: %d\n", array_size);
    
    // Память под массив
        
    array = (int *) calloc(array_size, sizeof(int));

    if (NULL == array)
    {
        error = true;
        puts("Память под массив не выделена!");
        goto finally;
    }

    puts("Исходный массив:");
    for (int i = 0; i < array_size; i++)
    {
	array[i] = i + 1;
        printf("%5d", array[i]);
    }
    puts("");

    for (int i = 0; i < array_size / 2; i++)
    {
        int tmp = array[i];
        array[i] = array[(array_size - 1) - i];
        array[(array_size - 1) - i] = tmp;
    }

    // Выводим

    puts("Перевернули:");
    for (int i = 0; i < array_size; i++)
    {
        printf("%5d", array[i]);
    }
    puts("");

 finally:
    
    if (NULL != array)
    {
        free(array);
    }

    return error;
}
