#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

typedef struct object{
    char fio[90];
    int age;
    int year;
    int id;
    struct object* next;
}STUDENT;

STUDENT* push_student(STUDENT* head, char fio[90], int age, int year, int id)
{
    STUDENT* ptr_student = malloc(sizeof(STUDENT));
    strncpy(ptr_student->fio, fio, sizeof(ptr_student->fio));
    ptr_student->fio[sizeof(ptr_student->fio)-1] = 0;
    ptr_student->age = age;
    ptr_student->year = year;
    ptr_student->id = id;
    ptr_student->next = head;
    return ptr_student;
}

int get_number()
{
    int len_num, int_num;
    while (1) {
        puts("\nВведите номер студента, которого хотите удалить: ");
        char num[40];
        fgets(num, sizeof(num), stdin);
        num[strcspn(num, "\n")] = 0;
        if (sscanf(num, "%d%n", &int_num, &len_num) == 1 && len_num == strlen(num) && int_num > 0) {
            break; //int_num - переменная, содержащая значение номера
        } else {
            puts("\nНекорректный ввод!");
        }
    }
    return int_num;
}

void show_students(STUDENT** head)
{
    STUDENT* start = *head;
    int cnt = 0;

    STUDENT* tmp = start;
    printf("\n------------Вывод всех студентов------------");
    while (tmp != NULL) {
        cnt++;
        printf("\n~~~ №: %d ~~~", cnt);
        printf("\nФИО: %s;\nВозраст: %d;\nКурс: %d; \nID: %d",
        tmp->fio, tmp->age, tmp->year, tmp->id);
        puts("\n--------------------------------------");
        tmp = tmp->next;
    }

    if (cnt == 0) {
        printf("\nСтуденты не найдены!");
        return;
    }
    puts("\n================================");
    puts("\n~~(для выполнения операции введите номер операции в консоль)~~");
    puts("\n[1] - удалить студента с номером X");
    puts("\n[2] - вернуться в меню");
    puts("\nоперация: ");
    char str[50];
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")]=0;
    if (strlen(str)==1&&strcspn(str, "1")!=strlen(str)) {
        int num = get_number();
        int cur_cnt = 0;

        STUDENT *cur = start;
        STUDENT *prev = NULL;

        while (cur != NULL) {
            cur_cnt++;
            if (cur_cnt == num) {
                if (prev == NULL)
                    *head = cur->next;
                else
                    prev->next = cur->next;

                printf("\nУдален студент с ФИО %s; Возраст %d; Курс %d; ID %d", cur->fio, cur->age, cur->year, cur->id);
                free(cur);
                return;
            }
            prev = cur;
            cur = cur->next;
        }
    }
    else if (strlen(str)==1&&strcspn(str, "2")!=strlen(str)){
        return;
    }
}

STUDENT* new_student(STUDENT* head, int id)
{
    char* ptr_fio;
    int* ptr_age;
    int* ptr_year;
    puts("\n_________Добавление студента_________\n");
    while(1){
        {
            puts("+++++++++++++++++++++++++++++++++++++");
            puts("\nДобавить студента? (y/n)");
            int ans = 0;
            while(1) {
                ans = getch();
                if (ans == 121 || ans == 110) //ASCII код y=121 n=110
                    break;
            }
            if (ans == 110)
                return head;
        }
        char fio[90];
        puts("Введите ФИО: ");
        fgets(fio, sizeof(fio), stdin);
        fio[strcspn(fio, "\n")] = 0;
        ptr_fio = fio;
        int len_age, int_age;
        while (1) {
            puts("Введите возраст:");
            char age[40];
            fgets(age, sizeof(age), stdin);
            age[strcspn(age, "\n")] = 0;
            if (sscanf(age, "%d%n", &int_age, &len_age) == 1 && len_age == strlen(age) && int_age > 0) {
                break; //int_age - переменная, содержащая значение возраста
            } else {
                puts("\nНекорректный ввод! Введите возраст: ");
            }
        }
        ptr_age = &int_age;
        int len_year, int_year;
        while (1) {
            puts("Введите курс обучения: ");
            char year[20];
            fgets(year, sizeof(year), stdin);
            year[strcspn(year, "\n")] = 0;
            if (sscanf(year, "%d%n", &int_year, &len_year) == 1 && len_year == strlen(year) && int_year > 0 && int_year <= 10) {
                break; //int_year - переменная, содержащая значение текущего курса обучения
            } else {
                puts("\nНекорректный ввод!");
            }
        }
        ptr_year = &int_year;
        puts("\n~~~~~~~~~~~~~~~~~~~~~~");
        printf("Студенту будет присвоен ID: %d", id);
        printf("\nУказаны следующие данные о новом студенте:\nФИО: %s;\nВозраст: %d;\nКурс: %d\nОни верны? (y/n)", fio, int_age, int_year);
        int ans = 0;
        while(1) {
            ans = getch();
            if (ans == 121 || ans == 110) //ASCII код y=121 n=110
                break;
        }
        if (ans == 121)
            break;
    }
    return push_student(head, ptr_fio, *ptr_age, *ptr_year, id);
}





void filter_id(STUDENT** head, int id)
{
    STUDENT* start = *head;
    int cnt = 0;
    printf("\n------------Поиск по ID=%d------------", id);
    STUDENT* tmp = start;
    while (tmp != NULL) {
        if (tmp->id == id) {
            cnt++;
            printf("\n~~~ №: %d ~~~", cnt);
            printf("\nФИО: %s;\nВозраст: %d;\nКурс: %d; \nID: %d",
                   tmp->fio, tmp->age, tmp->year, tmp->id);
            puts("\n--------------------------------------");
        }
        tmp = tmp->next;
    }

    if (cnt == 0) {
        printf("\nСтуденты с ID=%d не найдены!", id);
        return;
    }
    puts("\n================================");
    puts("\n~~(для выполнения операции введите номер операции в консоль)~~");
    puts("\n[1] - удалить студента с номером X");
    puts("\n[2] - вернуться в меню");
    puts("\nоперация: ");
    char str[50];
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")]=0;
    if (strlen(str)==1&&strcspn(str, "1")!=strlen(str)) {
        int num = get_number();
        int cur_cnt = 0;

        STUDENT *cur = start;
        STUDENT *prev = NULL;

        while (cur != NULL) {
            if (cur->id == id) {
                cur_cnt++;
                if (cur_cnt == num) {
                    if (prev == NULL)
                        *head = cur->next;
                    else
                        prev->next = cur->next;

                    printf("\nУдален студент с ФИО %s; Возраст %d; Курс %d; ID %d", cur->fio, cur->age, cur->year,
                           cur->id);
                    free(cur);
                    return;
                }
            }
            prev = cur;
            cur = cur->next;
        }
    }
    else if (strlen(str)==1&&strcspn(str, "2")!=strlen(str)) {
        return;
    }
}

void filter_age(STUDENT** head, int age)
{
    STUDENT* start = *head;
    int cnt = 0;
    printf("\n------------Поиск по возрасту, равному %d------------", age);
    STUDENT* tmp = start;
    while (tmp != NULL) {
        if (tmp->age == age) {
            cnt++;
            printf("\n~~~~~~~~~ №: %d ~~~~~~~~~", cnt);
            printf("\nФИО: %s;\nВозраст: %d;\nКурс: %d; \nID: %d",
                   tmp->fio, tmp->age, tmp->year, tmp->id);
            puts("\n--------------------------------------");
        }
        tmp = tmp->next;
    }

    if (cnt == 0) {
        printf("\nСтуденты с возрастом %d не найдены!", age);
        return;
    }
    puts("\n================================");
    puts("\n~~(для выполнения операции введите номер операции в консоль)~~");
    puts("\n[1] - удалить студента с номером X");
    puts("\n[2] - вернуться в меню");
    puts("\nоперация: ");
    char str[50];
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")]=0;
    if (strlen(str)==1&&strcspn(str, "1")!=strlen(str)) {
        int num = get_number();
        int cur_cnt = 0;

        STUDENT *cur = start;
        STUDENT *prev = NULL;

        while (cur != NULL) {
            if (cur->age == age) {
                cur_cnt++;
                if (cur_cnt == num) {
                    if (prev == NULL)
                        *head = cur->next;
                    else
                        prev->next = cur->next;

                    printf("\nУдален студент с ФИО %s; Возраст %d; Курс %d; ID %d", cur->fio, cur->age, cur->year,
                           cur->id);
                    free(cur);
                    return;
                }
            }
            prev = cur;
            cur = cur->next;
        }
    }
    else if (strlen(str)==1&&strcspn(str, "2")!=strlen(str)) {
        return;
    }
}

void filter_year(STUDENT** head, int year)
{
    STUDENT* start = *head;
    int cnt = 0;
    printf("\n------------Поиск по %d курсу------------", year);
    STUDENT* tmp = start;
    while (tmp != NULL) {
        if (tmp->year == year) {
            cnt++;
            printf("\n~~~~~~~~~ №: %d ~~~~~~~~~", cnt);
            printf("\nФИО: %s;\nВозраст: %d;\nКурс: %d; \nID: %d",
                   tmp->fio, tmp->age, tmp->year, tmp->id);
            puts("\n--------------------------------------");
        }
        tmp = tmp->next;
    }

    if (cnt == 0) {
        printf("\nСтуденты %d курса не найдены!", year);
        return;
    }
    puts("\n================================");
    puts("\n~~(для выполнения операции введите номер операции в консоль)~~");
    puts("\n[1] - удалить студента с номером X");
    puts("\n[2] - вернуться в меню");
    puts("\nоперация: ");
    char str[50];
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")]=0;
    if (strlen(str)==1&&strcspn(str, "1")!=strlen(str)) {
        int num = get_number();
        int cur_cnt = 0;

        STUDENT *cur = start;
        STUDENT *prev = NULL;

        while (cur != NULL) {
            if (cur->year == year) {
                cur_cnt++;
                if (cur_cnt == num) {
                    if (prev == NULL)
                        *head = cur->next;
                    else
                        prev->next = cur->next;

                    printf("\nУдален студент с ФИО %s; Возраст %d; Курс %d; ID %d", cur->fio, cur->age, cur->year,
                           cur->id);
                    free(cur);
                    return;
                }
            }
            prev = cur;
            cur = cur->next;
        }
    }
    else if (strlen(str)==1&&strcspn(str, "2")!=strlen(str)) {
        return;
    }
}

void filter_fio(STUDENT** head, char* fio)
{
    STUDENT* start = *head;
    int cnt = 0;
    printf("\n------------Поиск по подстроке \"%s\" в ФИО------------", fio);
    STUDENT* tmp = start;
    while (tmp != NULL) {
        if (strstr(tmp->fio, fio)) {
            cnt++;
            printf("\n~~~~~~~~~ №: %d ~~~~~~~~~", cnt);
            printf("\nФИО: %s;\nВозраст: %d;\nКурс: %d; \nID: %d",
                   tmp->fio, tmp->age, tmp->year, tmp->id);
            puts("\n--------------------------------------");
        }
        tmp = tmp->next;
    }

    if (cnt == 0) {
        printf("\nСтуденты с подстрокой \"%s\" в ФИО не найдены!", fio);
        return;
    }
    puts("\n================================");
    puts("\n~~(для выполнения операции введите номер операции в консоль)~~");
    puts("\n[1] - удалить студента с номером X");
    puts("\n[2] - вернуться в меню");
    puts("\nоперация: ");
    char str[50];
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")]=0;
    if (strlen(str)==1&&strcspn(str, "1")!=strlen(str)) {
        int num = get_number();
        int cur_cnt = 0;

        STUDENT *cur = start;
        STUDENT *prev = NULL;

        while (cur != NULL) {
            if (strstr(cur->fio, fio)) {
                cur_cnt++;
                if (cur_cnt == num) {
                    if (prev == NULL)
                        *head = cur->next;
                    else
                        prev->next = cur->next;

                    printf("\nУдален студент с ФИО %s; Возраст %d; Курс %d; ID %d", cur->fio, cur->age, cur->year,
                           cur->id);
                    free(cur);
                    return;
                }
            }
            prev = cur;
            cur = cur->next;
        }
    }
    else if (strlen(str)==1&&strcspn(str, "2")!=strlen(str)) {
        return;
    }
}

void menu(STUDENT** head, int* id)
{
    char str[50];
    puts("\n-=-=-=-=-=-=-=-Реестр студентов-=-=-=-=-=-=-=-");
    puts("\n~~(для выполнения операции введите номер операции в консоль)~~");
    puts("\n[1] - добавить нового студента");
    puts("\n[2] - вывести полный список");
    puts("\n[3] - поиск по id");
    puts("\n[4] - поиск по возрасту");
    puts("\n[5] - поиск по курсу");
    puts("\n[6] - поиск по фамилии, имени или отчеству");
    puts("\nоперация: ");
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")]=0;
    printf("\n---------------------------------------------");
    if (strlen(str)==1&&strcspn(str, "1")!=strlen(str)){
        *id += 1;
        *head = new_student(*head, *id);
    }
    else if (strlen(str)==1&&strcspn(str, "2")!=strlen(str)){
        show_students(head);
    }
    else if (strlen(str)==1&&strcspn(str, "3")!=strlen(str)){
        int len_id, int_id;
        while (1) {
            puts("\nВведите ID для поиска:");
            char id[40];
            fgets(id, sizeof(id), stdin);
            id[strcspn(id, "\n")] = 0;
            if (sscanf(id, "%d%n", &int_id, &len_id) == 1 && len_id == strlen(id) && int_id > 0) {
                break;
            } else {
                puts("\nНекорректный ввод!");
            }
        }
        filter_id(head, int_id);
    }
    else if (strlen(str)==1&&strcspn(str, "4")!=strlen(str)){
        int len_age, int_age;
        while (1) {
            puts("\nВведите возраст для поиска:");
            char age[40];
            fgets(age, sizeof(age), stdin);
            age[strcspn(age, "\n")] = 0;
            if (sscanf(age, "%d%n", &int_age, &len_age) == 1 && len_age == strlen(age) && int_age > 0) {
                break;
            } else {
                puts("\nНекорректный ввод!");
            }
        }
        filter_age(head, int_age);
    }
    else if (strlen(str)==1&&strcspn(str, "5")!=strlen(str)){
        int len_year, int_year;
        while (1) {
            puts("\nВведите курс для поиска:");
            char year[40];
            fgets(year, sizeof(year), stdin);
            year[strcspn(year, "\n")] = 0;
            if (sscanf(year, "%d%n", &int_year, &len_year) == 1 && len_year == strlen(year) && int_year > 0) {
                break;
            } else {
                puts("\nНекорректный ввод!");
            }
        }
        filter_year(head, int_year);
    }
    else if (strlen(str)==1&&strcspn(str, "6")!=strlen(str)){
        char fio[90];
        puts("\nВведите фамилию, имя, отчество или их часть с учетом регистра для поиска: ");
        fgets(fio, sizeof(fio), stdin);
        fio[strcspn(fio, "\n")] = 0;
        filter_fio(head, fio);
    }
}

int main()
{
    int id = 0;
    setlocale(LC_ALL, "");
    STUDENT* head = NULL;
    while(1){
        menu(&head, &id);
    }
    getch();
    return 0;
}
