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

void matrix_print(int** mat, int M, int N){
    for(int m=0; m<M; m++){
            printf("\n");
            printf("    ");
        for(int n=0; n<N; n++){
            printf(" %6d ", mat[m][n]);
        }
    }
}

int matrix_det(int** a, int M){
    if(M==3){
        int d = a[0][0]*a[1][1]*a[2][2]+a[0][1]*a[1][2]*a[2][0]+a[1][0]*a[2][1]*a[0][2]-a[2][0]*a[1][1]*a[0][2]-a[1][0]*a[0][1]*a[2][2]-a[2][1]*a[1][2]*a[0][0];
        return d;
        }
    if(M==2){
        int d = a[0][0]*a[1][1]-a[1][0]*a[0][1];
        return d;
        }
    if(M==1){
        int d = a[0][0];
        return d;
        }
    else{
        int sum=0; //сумма алг дополнений, умноженные на текущий элемент (когда он нечетный)
        int dif=0; //сумма алг дополнений, умноженные на текущий элемент (когда он четный)
        //далее sum-dif --- значение детерминанта
        int** rw = malloc(4*(M-1)); //инициализация матрицы меньшего порядка и заполнение ее нулями
        for(int m=0; m<M-1; m++){
            int* cl = malloc(4*(M-1));
            rw[m]=cl;
            for(int n=0; n<M-1; n++){
                rw[m][n]=0;
            }
        }
        for(int k=0; k<M; k++){ //элемент первой строки, для которого высчитывается алгебраическое дополнение
            for(int row=1;row<M;row++){ //кол-во строчек алг доп и рассматриваемых строк исходной матрицы одинаковое, строчки алг доп будут считаться row-1
                int elem_read=0; //номер элемента исходной матрицы, который читается из исходной матрицы, какждую итерацию увеличивается на
                int elem_write=0; //номер элемента новой матрицы, куда записывается подходящие по условиям ниже значение из исходной матрицы
                for(elem_read,elem_write;(elem_read<M)&&(elem_write<M-1);elem_read++){
                    if(elem_read==k){
                        continue;
                    }
                    else{
                        rw[row-1][elem_write]=a[row][elem_read];
                        elem_write++;
                    }
                }
            }
            //теперь мы имеем новую матрицу rw с порядком M-1, которая заполнена элементами исходной матрицы без вычеркнутой строки 1 и вычеркнутого столбца k
            //нам нужно найти ее детерминант рекурсивно и прибавить значение детерминанта, умноженное на элемент либо к sum либо к dif
            int d_mult_elem=matrix_det(rw, M-1)*a[0][k];
            if(k%2==0){ //делаем наоборот: для четных элементов прибавляем к сумме, т.к. в си элементы на -1 ближе к нулю
                sum+=d_mult_elem;
            }
            else{
                dif+=d_mult_elem;
            }
        }
        free(rw);
        return sum-dif;
    }
}


int main(){
    setlocale(LC_ALL,"");
    while(1){
        printf("\nЗадайте размеры матрицы(MxN)");
        int M=input_mat_m();
        int N=input_mat_n();
        int** matrix = matrix_init(M,N);
        printf("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n");
        printf("\n\n\n--------- Задана матрица ---------");
        matrix_print(matrix, M, N);
        printf("\n----------------------------------");
        if(M==N){
            int deter = matrix_det(matrix,M);
            printf("\n^^^^ Дана квадратная матрица %d-ого порядка. Определитель матрицы = %d ^^^^\n\n\n",M,deter);
        }
        else{
            printf("\n^^^^ Дана неквадратная матрица размером %d на %d. Невозможно вычислить определитель ^^^^\n\n\n",M,N);
        }
        printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n");
    }
    return 0;
}
