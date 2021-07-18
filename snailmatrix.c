/** Заполнение "улиткой" квадратной матрицы порядка N  
 * @file snailmatrix.c
 * @author VKorastelev
 * 
 * @detailed Матрица заполняется с элемента [0][0] по часовой стрелке
 Определяем количество вложенных "витков улитки" - контуров матрицы, 
 целочисленным делением размера на 2, (т.к. каждый контур уменьшает
 размер матрицы которую нужно обойти на 2).
 Если матрица имеет нечетный размер (3, 5, 7,...), центр заполняем 
 отдельно.
 В контуре заполняем строки слева направо, потом столбцы снизу вверх.  
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

    puts("Введите порядок N квадратной матрицы NxN (целое положительное число в диапазоне от 1 до 100): ");

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

    for (int i = 0; i < matrix_size; i++)
    {
	for (int j = 0; j < matrix_size; j++)
	{
	    matrix[i][j] = 0;
	}
    }

    int max_num_outline = matrix_size / 2;   // Количество контуров (вложенных матриц, витков)

    int init_num = 1; // Начальное значение заполнителя

    for (int current_outline = 0; current_outline < max_num_outline; current_outline++)
    {
        // Размер контрура
        int size_current_outline = matrix_size - 2 * current_outline;

        // Меньшие значения заполнителя (инкрементируются), левый верхний - [0][0]
        int num_low = init_num;

        // Большие значения заполнителя (декрементируются), левый нижний, напрмер, в матрице 3х3 - [2][0] 
        int num_high = init_num + 3 * (size_current_outline - 1);

        // Строки
	for (int j = current_outline; j < current_outline + size_current_outline; j++)
	{
            matrix[current_outline][j] = num_low++;
            matrix[current_outline + size_current_outline - 1][j] = num_high--;
        }

        num_low += 2 * (size_current_outline - 1);

        // Столбцы заполняем снизу вверх не заполняя строки ( -2)
        for (int i = current_outline + size_current_outline - 2; i > current_outline; i--)
	{
	    matrix[i][current_outline] = num_low++;
	    matrix[i][current_outline + size_current_outline - 1] = num_high--;
        }

        init_num= num_low;
    }

    // Заполняем центр у матриц с нечетным размером 
    if (1 == (matrix_size % 2))
    {
	matrix[(matrix_size - 1) / 2][(matrix_size - 1) / 2] = init_num;
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
