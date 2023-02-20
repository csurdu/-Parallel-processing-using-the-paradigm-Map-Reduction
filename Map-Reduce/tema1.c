#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

pthread_mutex_t mutex;
pthread_barrier_t barrier;
struct structura_thread
{
    char **lista_fisiere;
    int *numar_fisiere;
    int max_size;
    pthread_mutex_t *mutex;
    int maperi;
    int reduceri;
    int id;
    int ***mat;
    int *contor;
    int *contor_reduceri;
    int ***matricebengoasa;
    int **matrice_reduceri;
};

int checkPerfectNumber(
    long int N,
    long int start,
    long int last,
    int exp)
{

    long int mid = (start + last) / 2;

    if (start > last)
    {
        return -1;
    }

    if (pow(mid, exp) == N)
    {
        return mid;
    }

    else if (pow(mid, exp) > N)
    {
        return checkPerfectNumber(
            N, start, mid - 1, exp);
    }

    else
    {
        return checkPerfectNumber(
            N, mid + 1, last, exp);
    }
}

void quicksort(int number[25], int first, int last)
{
    int i, j, pivot, temp;

    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;

        while (i < j)
        {
            while (number[i] <= number[pivot] && i < last)
                i++;
            while (number[j] > number[pivot])
                j--;
            if (i < j)
            {
                temp = number[i];
                number[i] = number[j];
                number[j] = temp;
            }
        }

        temp = number[pivot];
        number[pivot] = number[j];
        number[j] = temp;
        quicksort(number, first, j - 1);
        quicksort(number, j + 1, last);
    }
}

int RemoveDuplicates(int arr[100], int n)
{
    if (n == 0 || n == 1)
        return n;

    int temp[n];

    int j = 0;

    for (int i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1])
            temp[j++] = arr[i];

    temp[j++] = arr[n - 1];

    for (int i = 0; i < j; i++)
        arr[i] = temp[i];

    return j;
}

void *f(void *arg)
{
    struct structura_thread *my_data;
    my_data = (struct stuctura_thread *)arg;
    char filename[256];
    int i;
    int j;

    int numar_puteri[1000];
    if (my_data->id <= my_data->maperi || my_data->id == 0)
    {
        int j = 0;
        int P = my_data->maperi;
        int N = my_data->max_size;
        int lista_puteri[1000][1000];
        pthread_mutex_lock(&mutex);
        int start = my_data->id * N / P;
        int end;

        if ((my_data->id + 1) * N / P > N)
            end = N;
        else
        {
            end = (my_data->id + 1) * N / P;
        }
        for (int i = start; i < end; i++)
        {

            FILE *fp = fopen(my_data->lista_fisiere[i], "r");
            if (fp == NULL)
            {
                printf("Error: could not open file %s\n", my_data->lista_fisiere[i]);
            }
            j = 0;

            char buffer[256];
            fgets(buffer, 256, fp);

            while (fgets(buffer, 256, fp))
            {

                for (int z = 2; z <= my_data->reduceri + 1; z++)
                {
                    if (checkPerfectNumber(atoi(buffer), 1, atoi(buffer), z) >= 0)
                    {

                        my_data->mat[my_data->id][z][my_data->contor[z]] = atoi(buffer);

                        my_data->contor[z] = my_data->contor[z] + 1;
                    }
                }
                j++;
            }
            fclose(fp);
        }

        pthread_mutex_unlock(&mutex);
    }
    pthread_barrier_wait(&barrier);

    if (my_data->id >= my_data->maperi)
    {
        pthread_mutex_lock(&mutex);
        int a;
        int nr = my_data->id - my_data->maperi + 2;
        if (my_data->maperi == 1)
        {
            nr = my_data->id + 1;
        }
        for (int i = 0; i < my_data->maperi; i++)
        {
            for (int z = 0; z < 106; z++)
            {
                if (my_data->mat[i][nr][z])
                {
                    my_data->matrice_reduceri[nr][my_data->contor_reduceri[nr]] = my_data->mat[i][nr][z];

                    my_data->contor_reduceri[nr] = my_data->contor_reduceri[nr] + 1;
                }
                else
                {
                    break;
                }
            }
        }

        quicksort(my_data->matrice_reduceri[nr], 0, my_data->contor_reduceri[nr] - 1);

        int rezultat;
        rezultat = RemoveDuplicates(my_data->matrice_reduceri[nr], my_data->contor_reduceri[nr]);
        char out[20];
        sprintf(out, "out%d.txt", nr);
        FILE *fp = fopen(out, "w");

        if (fp == NULL)
        {
            printf("Error: could not open file %s", filename);
            return -1;
        }
        fprintf(fp, "%d", rezultat);
        fclose(fp);

        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char *argv[])
{

    int i = 0;
    int numar_fisiere = 0;
    int maperi = atoi(argv[1]);
    int reduceri = atoi(argv[2]);

    int a;
    char filename[100];

    strcpy(filename, argv[3]);

    // strcat(filename, "/test.txt");
    int r;
    void *status;
    pthread_t threads[maperi];

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    char buffer[256];
    fscanf(fp, "%d", &a);
    char **file_list = malloc(a * sizeof(char *));
    for (i = 0; i < a; i++)
    {
        file_list[i] = malloc(20 * sizeof(char));
    }

    while (numar_fisiere < a)
    {
        fscanf(fp, "%s", file_list[numar_fisiere]);

        numar_fisiere++;
    }

    fclose(fp);

    struct structura_thread *structura_tread;
    structura_tread = (struct structura_thread *)malloc(sizeof(struct structura_thread) * 1000);

    int **matrice_reduceri;
    matrice_reduceri = (int **)malloc(1000 * sizeof(int *));
    for (int i = 0; i < 1000; i++)
    {
        matrice_reduceri[i] = malloc(20 * sizeof(int));
    }
    int ***mat = (int ***)malloc(100 * sizeof(int **));
    for (int k = 0; k < 100; k++)
    {
        mat[k] = (int **)malloc(sizeof(int *) * 100);
        for (int j = 0; j < 100; j++)
        {
            mat[k][j] = (int *)malloc(sizeof(int) * 100);
        }
    }
    for (int z = 0; z < maperi + reduceri; z++)
    {
        structura_tread[z].maperi = maperi;
        structura_tread[z].reduceri = reduceri;
        structura_tread[z].max_size = a;
        structura_tread[z].lista_fisiere = file_list;
        structura_tread[z].contor = (int *)malloc(100 * sizeof(int));
        structura_tread[z].mat = mat;
        structura_tread[z].matrice_reduceri = matrice_reduceri;
        structura_tread[z].contor_reduceri = (int *)malloc(100 * sizeof(int));
    }

    pthread_mutex_init(&mutex, NULL);

    pthread_barrier_init(&barrier, NULL, maperi + reduceri);

    for (i = 0; i < maperi + reduceri; i++)
    {

        structura_tread[i].id = i;

        r = pthread_create(&threads[i], NULL, f, &structura_tread[i]);

        if (r)
        {
            printf("Eroare la crearea thread-ului %d\n", i);
            exit(-1);
        }
    }

    for (i = 0; i < maperi + reduceri; i++)
    {
        r = pthread_join(threads[i], &status);

        if (r)
        {
            printf("Eroare la asteptarea thread-ului %d\n", i);
            exit(-1);
        }
    }

    return 0;
}
