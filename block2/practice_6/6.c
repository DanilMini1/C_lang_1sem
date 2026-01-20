#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

//ввод логина
char* getname(){
    static char str[100];
    while(1){
        printf("\nЛогин: ");
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")]=0;
        if (strlen(str)<3){
            printf("\nЛогин не может быть короче 3 символов!");
        }
        else if (strcspn(str, " /`!@#$%^&*()_+/-=/[/]{};':\"|,.<>//?~")!=strlen(str)){
            printf("\nЛогин не может содержать специальные символы или пропуски!");
        }
        else{
            return str;
        }
    }
}


char* new_getpass(){
    while(1){
        static char str[50];
        printf("\nПароль: ");
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")]=0;
        if (strlen(str)<7){
            printf("\nПароль должен быть длиной не менее 6 символов!");
        }
        else if (strcspn(str, " ")!=strlen(str)){
            printf("\nПароль не может содержать пропуски!");
        }
        else if (strcspn(str, "/`!@#$%^&*()_+/-=/[/]{};':\"|,.<>//?~")==strlen(str)){
            printf("\nПароль должен содержать специальные символы!");
        }
        else{
            return str;
        }
    }
}

char* getpass(){
    while(1){
        static char str[50];
        printf("\nПароль: ");
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")]=0;
        if (strlen(str)<1){
            printf("\nПоле не может быть пустым");
        }
        else{
            return str;
        }
    }
}

int account_create(char* file_name, char* nickname){
        char str[50];
        printf("\nТакого аккаунта не существует. Создать новый? (y/n): ");
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")]=0;
        if (strlen(str)==1&&strcspn(str, "y")!=strlen(str)){
            FILE* f = fopen(file_name, "w+");
            printf("\nСоздайте пароль для аккаунта %s!",nickname);
            char* pass = new_getpass();
            fwrite(pass,sizeof(char),strlen(pass),f);
            fclose(f);
            printf("\nАккаунт для %s создан!",nickname);
            return 0;
        }
        else if (strlen(str)==1&&strcspn(str, "n")!=strlen(str)){
            return 1;
        }
    }



int auth(FILE* file, char* nickname){
    printf("\nВведите пароль для пользователя %s.", nickname);
    char* pass = getpass();
    char file_pass[50];
    fgets(file_pass, sizeof(file_pass), file);
    file_pass[strcspn(pass, "\n")] = 0;
    if (!pass) {
        printf("\nОшибка при вводе пароля.\n");
        return 0;
    }
    if (strcmp(pass, file_pass) == 0) {
        printf("\nДобро пожаловать, %s!\n", nickname);
        return 1;
    } else {
        printf("\nНеверный пароль!\n");
        return 0;
    }
}

int main(){
    setlocale(LC_ALL, "");
    while(1){
        char* name = getname();
        char f_name[120];
        snprintf(f_name, sizeof(f_name), "users\\%s.txt", name);
        FILE* f = fopen(f_name,"r");
        if (f==NULL){
        account_create(f_name,name);
        }
        else if (f!=NULL){
            auth(f, name);
        }
    }
    return 0;
}
