/** Заполнение верхнетреугольной матрицы порядка N  
 * @file triangularmatrix.c
 * @author VKorastelev
 * 
 * @detailed  
 *  
 */

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {

    setlocale(LC_ALL, "RU");

    bool error = false;
    // Двумерный массив (матрица)
    int **matrix = NULL;
    int matrix_size = 0;

    puts("Введите порядок N верхнетреугольной матрицы NxN (целое положительное число в диапазоне от 1 до 100): ");

    while (scanf("%d", &matrix_size) != 1 || (matrix_size < 1 || matrix_size > 100))
    {
        char ch_trash;
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

    printf("Верхнетреугольная матрица %dx%d:\n", matrix_size, matrix_size);
    
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

    for (int i = 0; i < matrix_size; i++)
    {
	for (int j = i; j < matrix_size; j++)
	{
	    matrix[i][j] = 1;
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
