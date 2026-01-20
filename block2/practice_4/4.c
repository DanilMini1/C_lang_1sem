#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
int* mass_init(int len){ //резервация памяти для массива
    return calloc(len, 4);
}

int* mass_sort(int* mass){ //ф-ия сортировки
    int cnt=0;
    int len = sizeof(mass)/sizeof(mass[0]);
    do{
        cnt=0;
        for(int num = 0; num<=len;num++){
            int wait;
            if((mass[num]>mass[num+1])&&(num+1<len)){
                wait = mass[num];
                mass[num]=mass[num+1];
                mass[num+1]=wait;
                cnt+=1;
            }
        }
    } while(cnt>0);
    return 0;
}


int get_input(){
    char lenght_o_m[50];
    while(1){
        fgets(lenght_o_m,sizeof(lenght_o_m),stdin);
            lenght_o_m[strcspn(lenght_o_m,"\n")]=0;
            int str_len, temp;
            if(sscanf(lenght_o_m,"%d%n",&temp,&str_len)==1&&str_len==strlen(lenght_o_m)&&temp>0){
                    return temp;
               }
            else{
                printf("\nНекорректный ввод! Введите целое число: ");
        }

    }
}

void mass_crt(int len, int* mass){
    printf("\nВаш массив состоит из %d элементов.",len);
    for(int num=1; num<=len;num++){
        printf("\nОбозначьте элемент #%d: ",num);
        mass[num-1]=get_input();
    }
}

void mass_output(int* mass){
    for(int num=0;num<sizeof(mass)/sizeof(mass[0]);num++){
        printf("\nэлемент #%d: %d",num+1,mass[num]);
    }
}

int* mass_copy(int* mass){
    int* new_mass = mass_init(sizeof(mass)/sizeof(mass[0]));
    for (int num=0; num<sizeof(mass)/sizeof(mass[0]); num+=1){
        new_mass[num]=mass[num];
    }
    return new_mass;
}


int main(){
    setlocale(LC_ALL, "");
    printf("\nВведите значение длины массива: ");
    int len_o_m = get_input();

    int* massive = mass_init(len_o_m);
    mass_crt(len_o_m,massive);
    int* cop_massive = mass_copy(massive);
    mass_sort(cop_massive);
    printf("\nОтсортированный массив:");
    mass_output(cop_massive);
    printf("\nНеотсортированный массив:");
    mass_output(massive);
    printf("\n%d", sizeof(*massive));
    return 0;
}
