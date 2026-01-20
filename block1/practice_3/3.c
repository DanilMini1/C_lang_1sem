#include <stdio.h>
int main(){
    int len=0; //длина массива
    printf("print len of massive: ");
    scanf("%d",&len); //запрос длины массива от пользователя
    int mass[len]; //выделение памяти для массива
    for(int cnt=0;cnt<len;cnt++){ //заполнение массива элементами от пользователя
        int numb=0;//переменная, принимающая значение от пользователя
        printf("\nprint elem num%d: ",cnt+1);
        scanf("%d",&numb);
        *(mass+cnt)=numb;
    }
    printf("\nunsorted massive:");
    for(int cnt_per=0;cnt_per<len;cnt_per++){ //вывод в консоль несортированных элементов массива
        int numb=0;
        printf("\nelem num%d: %d",cnt_per+1,mass[cnt_per]);
    }

    int cnt_while=0;//переменная обозначает количество итераций, в которых не было совершено обмена местами соседних элементов в массиве
    while(cnt_while<len-1){ //главный цикл с счетчиком, закончится, когда количество итераций цикла без обмена соседних элементов будет равно [длина-1]
        for(int cnt_sort=0;cnt_sort<len-1;cnt_sort++){ //цикл сортировки
            int wait=0;
            if(mass[cnt_sort]>mass[cnt_sort+1]){ //условие сортировки. сравнение первого и второго элемента
                wait=mass[cnt_sort]; //переменная для промежуточного хранения одного из элементов
                mass[cnt_sort]=mass[cnt_sort+1];
                mass[cnt_sort+1]=wait;
                cnt_while=0;//обнуление счетчика, так как произошла итерация с обменом элементов

            }
            else{
                cnt_while++;//увелечение счетчика на 1, т.к. итерация была совершена без обмена элементов значениями
            }

        }
    }
    printf("\n\nsorted massive:");
    for(int cnt_per=0;cnt_per<len;cnt_per++){ //вывод в консоль сортированных элементов массива
        int numb=0;
        printf("\nelem num%d: %d",cnt_per+1,mass[cnt_per]);
    }
    printf("\n\nmax elem: %d", mass[len-1]);
    printf("\nmin elem: %d", mass[0]);
    return 0;
}