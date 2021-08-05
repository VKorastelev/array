/** Заполнение числами квадратной матрицы порядка N 
 * @file squarematrix.c
 * @author VKorastelev
 * 
 * @detailed Матрица порядка N заполняется с элемента [0][0] числами от 1  
 *  
 */

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {

    setlocale(LC_ALL, "ru_RU.utf8");

    bool error = false;
    // Двумерный массив (матрица)
    int **matrix = NULL;
    int matrix_size = 0;

    puts("Введите порядок N квадратной матрицы NxN (целое положительное число в диапазоне"
        " от 1 до 100): ");

    while (scanf("%d", &matrix_size) != 1 || (matrix_size < 1 || matrix_size > 100))
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

    printf("Матрица %dx%d:\n", matrix_size, matrix_size);
    
    // Указатели на строки
        
    matrix = (int **) calloc(matrix_size, sizeof(int *));

    if (NULL == matrix)
    {
        error = true;
        puts("Память под указатели на строки не выделена!");
        goto finally;
    }

    // Строки
    for (int i = 0; i < matrix_size; i++)
    {
	matrix[i] = (int *) calloc(matrix_size, sizeof(int));
        if (NULL == matrix[i])
        {
            error = true;
            puts("Память под строки не выделена!");
            goto finally;
        } 
    }

    int curr_num = 1;

    for (int i = 0; i < matrix_size; i++)
    {
	for (int j = 0; j < matrix_size; j++)
	{
	    matrix[i][j] = curr_num++;
	}
    }

    // Выводим
    for (int i = 0; i < matrix_size; i++)
    {
	for (int j = 0; j < matrix_size; j++)
        {
            printf("%6d", matrix[i][j]);
	}
        printf("\n");
    }

 finally:
    // Освобождаем выделенную память строк
    for (int i = 0; i < matrix_size; i++)
    {
        if (NULL != matrix[i])
        {
            free(matrix[i]);
        }
    }

    // Указатели на строки
    if (NULL != matrix)
    {
        free(matrix);
    }

    return error;
}
