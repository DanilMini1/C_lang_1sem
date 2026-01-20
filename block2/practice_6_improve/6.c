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

char* get_key(){
    while(1){
        static char key[50];
        printf("\nВведите ключ шифрования: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = 0;
        char str[50];
        printf("\nКлюч шифрования \"%s\"? (y/n): ",key);
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")]=0;
        if (strlen(str)==1&&strcspn(str, "y")!=strlen(str)){
            return key;
        }
        else if (strlen(str)==1&&strcspn(str, "n")!=strlen(str)){
            continue;
        }
    }
}

void xor_encrypt_decrypt(char* pass, char* key) { //функция шифрует/дешифрует строку, полученную на вход, по ключу, ничего не возвращает, подаваемый указатель уже изменяется
    int pass_len = strlen(pass);
    int key_len = strlen(key);

    for (int i = 0; i < pass_len; i++) {
        pass[i] ^= key[i % key_len]; // побитовый XOR
    }
}

char* new_getpass(){
    while(1){
        static char str[50];
        printf("\nПароль: ");
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")]=0;
        if (strlen(str)<=5){
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

int account_create(char* file_name, char* nickname, char* key){
        char str[50];
        printf("\nТакого аккаунта не существует. Создать новый? (y/n): ");
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")]=0;
        if (strlen(str)==1&&strcspn(str, "y")!=strlen(str)){
            printf("\nСоздайте пароль для аккаунта %s!",nickname);
            char* pass = new_getpass();
            xor_encrypt_decrypt(pass, key);
            FILE* f = fopen(file_name, "w+");
            fwrite(pass,sizeof(char),strlen(pass),f);
            fclose(f);
            printf("\nАккаунт для %s создан!",nickname);
            return 0;
        }
        else if (strlen(str)==1&&strcspn(str, "n")!=strlen(str)){
            return 1;
        }
    }



int auth(FILE* file, char* nickname, char* key){
    printf("\nВведите пароль для пользователя %s.", nickname);
    char* pass = getpass();
    xor_encrypt_decrypt(pass,key);
    char file_pass[50];
    fgets(file_pass, sizeof(file_pass), file);
    file_pass[strcspn(file_pass, "\n")] = 0;
    if (!pass) {
        printf("\nОшибка при вводе пароля.\n");
        fclose(file);
        return 0;
    }
    if (strcmp(pass, file_pass) == 0) {
        printf("\nДобро пожаловать, %s!\n", nickname);
        rewind(file);
        return 1;
    } else {
        printf("\nНеверный пароль!\n");
        fclose(file);
        return 0;
    }
}

int main(){
    setlocale(LC_ALL, "");
    char* key = get_key();
    while(1){
        char* name = getname();
        char f_name[120];
        snprintf(f_name, sizeof(f_name), "users\\%s.txt", name);
        FILE* f = fopen(f_name,"r");
        if (f==NULL){
            account_create(f_name,name,key);
        }
        else if (f!=NULL){
            if (auth(f, name,key)==1){
                while(1){
                    char str[50];
                    printf("\n---------------------------------------------");
                    printf("\n~~(для выполнения операции введите номер операции в консоль)~~");
                    printf("\n[1] - посмотреть пароль");
                    printf("\n[2] - удалить аккаунт");
                    printf("\n[3] - сменить пароль");
                    printf("\n[4] - выйти из аккаунта");
                    printf("\nоперация: ");
                    fgets(str,sizeof(str),stdin);
                    str[strcspn(str, "\n")]=0;
                    printf("\n---------------------------------------------");
                    if (strlen(str)==1&&strcspn(str, "1")!=strlen(str)){
                        char file_pass_c[50];
                        fgets(file_pass_c, sizeof(file_pass_c), f);
                        file_pass_c[strcspn(file_pass_c, "\n")] = 0;
                        char* file_pass_main = file_pass_c;
                        xor_encrypt_decrypt(file_pass_main,key);
                        printf("\nПароль для \"%s\": %s", name, file_pass_main);
                    }
                    else if (strlen(str)==1&&strcspn(str, "2")!=strlen(str)){
                        char str_del[50];
                        printf("\nВы уверены, что хотите удалить аккаунт %s? (y/n): ",name);
                        fgets(str_del,sizeof(str_del),stdin);
                        str_del[strcspn(str_del, "\n")]=0;
                        if (strlen(str_del)==1&&strcspn(str_del, "y")!=strlen(str_del)){
                            fclose(f);
                            remove(f_name);
                            printf("Аккаунт %s успешно удален",name);
                            break;
                        }
                    }
                    else if (strlen(str)==1&&strcspn(str, "3")!=strlen(str)){
                        char str_ch[50];
                        printf("\nВы уверены, что хотите сменить пароль для аккаунта %s? (y/n): ",name);
                        fgets(str_ch,sizeof(str_ch),stdin);
                        str_ch[strcspn(str_ch, "\n")]=0;
                        if (strlen(str_ch)==1&&strcspn(str_ch, "y")!=strlen(str_ch)){
                            fclose(f);
                            remove(f_name);
                            FILE* f = fopen(f_name, "w+");
                            printf("\nСоздайте новый пароль для аккаунта %s!",name);
                            char* pass = new_getpass();
                            xor_encrypt_decrypt(pass, key);
                            fwrite(pass,sizeof(char),strlen(pass),f);
                            fclose(f);
                            printf("\nПароль для %s успешно изменен!",name);
                        }
                    }
                    else if (strlen(str)==1&&strcspn(str, "4")!=strlen(str)){
                        printf("\nДо свидания, %s!\n\n\n",name);
                        break;
                        fclose(f);
                    }
                }
            }
        }
    }
    return 0;
}
