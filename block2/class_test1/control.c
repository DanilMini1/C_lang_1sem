
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

int input(){
    while(1){
        printf("\nВведите целое число: ");
        char str[50];
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")]=0;
        int len_str, int_str;
        if(sscanf(str,"%d%n",&int_str,&len_str)==1&&len_str==strlen(str)&&int_str>0){
            return int_str;
        }
        else{
            printf("\nНекорректный ввод!");
        }
    }
}
int input_mat_m(){
    printf("\n----- Значение M(строки).");
    int m=input();
    printf("\nM=%d\n\n\n",m);
    return m;
}
int input_mat_n(){
    printf("\n----- Значение N(столбцы).");
    int n=input();
    printf("\nN=%d\n\n\n",n);
    return n;
}
int** matrix_init(int M, int N){
    int** rw = malloc(4*M);
    for(int m=0; m<M; m++){
        printf("\n--------- Заполните строку #%d. ---------",m+1);
        int* cl = malloc(4*N);
        rw[m]=cl;
        for(int n=0; n<N; n++){
            printf("\n\n~~~ Элемент #%d для строки #%d ~~~",n+1,m+1);
            rw[m][n]=input();
        }
    }
    return rw;
}


int** matrix_transp(int** mat,int M, int N){ //на вход подается матрица и ее размеры MxN
    int** rw = malloc(4*N);//инициализируется количество строк, равное количеству столбцов исходной матрицы
    for(int n=0; n<N; n++){
            int* cl = malloc(4*M);//инициализируется количество столбцов, равное количеству строк исходной матрицы
            rw[n]=cl;
            for(int m=0; m<M; m++){
                rw[n][m]=mat[m][n]; //элементу n строки m столбца транс. матрицы присваивается значение элемента m строки n столбца исх. матрицы
                printf("%d",mat[m][n]);
        }
        return rw; //возвращает транспонированную матрицу
    }
}

void matrix_print(int** mat, int M, int N){
    for(int m=0; m<M; m++){
            printf("\n");
            printf("    ");
        for(int n=0; n<N; n++){
            printf(" %6d ", mat[m][n]);
        }
    }
}
int main(){
    setlocale(LC_ALL, "");
    while(1){
        printf("\nЗадайте размеры матрицы(MxN)");
        int M=input_mat_m();
        int N=input_mat_n();
        int** matrix = matrix_init(M,N);
        printf("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n");
        printf("\n\n\n--------- Задана матрица ---------");
        matrix_print(matrix, M, N);
        printf("\n----------------------------------");
        int** matrix_t = matrix_transp(matrix,M,N);
        printf("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n");
        printf("\n\n\n--------- Транспонированная матрица ---------");
        matrix_print(matrix_t, N, M);
        printf("\n----------------------------------");
    }
    return 0;
}