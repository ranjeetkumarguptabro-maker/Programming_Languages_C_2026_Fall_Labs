/*
 * week4_1_dynamic_array.c
 * Author: Ranjeet Kumar Gupta
 * Student ID: 251ADB005
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    int *arr = NULL;
    int sum = 0;
    float average;

    printf("Enter number of elements: ");

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid size.\n");
        return 1;
    }

    /* Allocate memory for n integers */
    arr = malloc(n * sizeof(int));

    /* Check if memory allocation was successful */
    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* Read n integers */
    printf("Enter %d integers: ", n);

    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }

        sum += arr[i];
    }

    /* Calculate average using floating-point division */
    average = (float)sum / n;

    /* Print results */
    printf("Sum = %d\n", sum);
    printf("Average = %.2f\n", average);

    /* Free dynamically allocated memory */
    free(arr);

    return 0;
}