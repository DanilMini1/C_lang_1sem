#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define MAX_INVENTORY 5
#define MAX_NAME_LEN 30

typedef struct { //предмет
    int id;
    char name[MAX_NAME_LEN];
} Item;

typedef struct { //игрок
    int location_id;      //текущая локация
    int sanity;           //рассудок
    Item inventory[MAX_INVENTORY];
    int items_count;
    int cutscene_count;
    int opened_door;
} Player;

void init_player(Player *p)
{ //ф-ия инициализации игрока
    p->location_id = 0;
    p->sanity = 100;
    p->items_count = 0;
    p->cutscene_count = 0;
    p->opened_door = 0;
}

void add_item(Player *p, int item_id, const char *name)
{ //добавить предмет в инвентарь
    if (p->items_count < MAX_INVENTORY) {
        p->inventory[p->items_count].id = item_id;
        snprintf(p->inventory[p->items_count].name, MAX_NAME_LEN, "%s", name);
        p->items_count++;
        printf(">> В инвентарь добавлено: %s\n", name);
    } else {
        printf(">> Инвентарь полон!\n");
    }
}

int has_item(Player *p, int item_id)
{ //проверка наличия предмета по id
    for (int i = 0; i < p->items_count; i++) {
        if (p->inventory[i].id == item_id) {
            return 1;
        }
    }
    return 0;
}

void show_inventory(Player *p)
{
    printf("\n=========== ИНВЕНТАРЬ ===========\n");
    if (p->items_count == 0) {
        printf("(пусто)\n");
    } else {
        for (int i = 0; i < p->items_count; i++) {
            printf("> %s\n", p->inventory[i].name);
        }
    }
    printf("=================================\n");
}

void play_music(const char *filename, int repeat) //задний план музыка
{ //repeat = 1(повтор)/0(один проигрыш)
    char command[256];
    mciSendString("close myMusic", NULL, 0, NULL);
    sprintf(command, "open \"%s\" type mpegvideo alias myMusic", filename);
    mciSendString(command, NULL, 0, NULL);
    if (repeat) {
        mciSendString("play myMusic repeat", NULL, 0, NULL);
    } else {
        mciSendString("play myMusic", NULL, 0, NULL);
    }
}

void play_sfx(const char *filename) //звуковой эффект
{
    char command[256];
    mciSendString("close mySfx", NULL, 0, NULL);
    sprintf(command, "open \"%s\" type mpegvideo alias mySfx", filename);
    mciSendString(command, NULL, 0, NULL);
    mciSendString("play mySfx", NULL, 0, NULL);
}

void stop_music() //остановка заднеплановой музыки
{
    mciSendString("stop myMusic", NULL, 0, NULL);
    mciSendString("close myMusic", NULL, 0, NULL);
}

void stop_sfx() //эффекта
{
    mciSendString("stop mySfx", NULL, 0, NULL);
    mciSendString("close mySfx", NULL, 0, NULL);
}


void main_cls()
{ // очистка экрана
    system("cls");
}

void print_ascii_art(const char *filename, const int choose)
{ //choose = 0(постепенная печать)/1(мгновенная печать)
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка! Не удалось открыть файл с артом: %s\n", filename);
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
        fflush(stdout);
        if(choose == 0)
            Sleep(50);
    }
    fclose(file);
    printf("\n");
}
void print_text_typewriter(const char *filename, const int choose)
{ //choose = 0(постепенная печать)/1(мгновенная печать)
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка! Не удалось открыть файл с текстом: %s\n", filename);
        return;
    }
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
        fflush(stdout);
        if (choose == 0)
            Sleep(5);
    }
    fclose(file);
    printf("\n");
}

int get_player_choice(const char *options[], int count) {
    printf("\nВаши действия:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, options[i]);
    }
    puts("\n================================");
    puts("9. Открыть инвентарь");
    puts("0. Закрыть игру");
    int choice = 0;
    printf("\n> ");
    while (scanf("%d", &choice) != 1 || choice < 0 || (choice > count && choice != 9) ) {
        while(getchar() != '\n');
        printf("Неверный выбор. Попробуйте снова.\n> ");
    }
    while(getchar() != '\n');
    return choice;
}


int main()
{
    // Настройка кодировки
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Инициализация игрока
    Player player;
    init_player(&player);

    int game_running = 1;
    int game_closed = 0;

    print_ascii_art("locations\\intro_art0_0.txt", 0);\
    play_sfx("sfx\\intro_speech.mp3");
    print_text_typewriter("texts\\intro_text0_0.txt", 0);
    system("Pause");
    stop_sfx();
    play_sfx("sfx\\falling.mp3");
    Sleep(3000);

    while (game_running && player.sanity > 0) {
        main_cls();

        switch (player.location_id) {

            //1 локация
            case 0: {
                play_music("background\\ambient.mp3", 1);
                if (player.cutscene_count < 1) {
                    print_ascii_art("locations\\loc1_art0_0.txt", 0);
                    player.cutscene_count +=1 ;
                    }
                else {
                    print_ascii_art("locations\\loc1_art0_0.txt", 1);
                }
                puts("\nВы находитесь в темном желтом коридоре, вам в нос бьет невыносимый запах затхлости, как от старого влажного ковра..\n");
                puts("В середине длинного коридора словно всепоглощающая тьма..");

                const char *actions[] = {
                    "Идти вперед",
                    "Осмотреть пол",
                };
                int choice = get_player_choice(actions, 2);

                if (choice == 1) {
                    if (!has_item(&player, 1)) {
                    printf("Тут слишком темно... Мне нужен свет.\n");
                    system("pause");
                    } else {
                    printf("Луч фонарика освещает длинный коридор... Под ногами чувствуется влажность ковролина, которым устелен этот коридор.\n");
                    play_sfx("sfx\\steps.mp3");
                    player.location_id = 1;
                    Sleep(2000);
                    }
                } else if (choice == 2) {
                    if (!has_item(&player, 1)) {
                        printf("Вы нащупали что-то металлическое...\n");
                        Sleep(1000);
                        play_sfx("sfx\\pick_up.mp3");
                        add_item(&player, 1, "Фонарик");
                        system("pause");
                    } else {
                        printf("Тут больше ничего нет.\n");
                        system("pause");
                    }
                } else if (choice == 9) {
                    show_inventory(&player);
                    system("pause");
                } else if (choice == 0) {
                    game_running = 0;
                    game_closed = 1;
                }
                break;
            }

            // 2 локация
            case 1: {
                if (player.cutscene_count < 2) {
                    print_ascii_art("locations\\loc2_art0_0.txt", 0);
                    player.cutscene_count += 1;
                    }
                else {
                    print_ascii_art("locations\\loc2_art0_0.txt", 1);
                }
                puts("\nКоридор перед вами раздваивается.\n");

                const char *actions[] = {
                    "Пойти налево",
                    "Пойти направо",
                    "Вернуться назад"
                };
                int choice = get_player_choice(actions, 3);

                if (choice == 1) {
                    if(player.opened_door == 0)
                        {
                        print_ascii_art("locations\\loc2_art0_1.txt", 1);
                        puts("Белая деревянная дверь преграждает путь.\n");
                        Sleep(1000);
                        if (has_item(&player, 2)) {
                             printf("Вы открыли дверь ключом!\n");
                             play_sfx("sfx\\door2.mp3");
                             Sleep(2000);
                             play_sfx("sfx\\steps.mp3");
                             Sleep(3000);
                             player.opened_door = 1;
                             player.location_id = 2;
                        } else {
                             printf("Нужен ключ.\n");
                        }
                        system("pause");
                        }
                    else
                        {
                        puts("Вы проходите через уже открытую ранее дверь. ");
                        play_sfx("sfx\\steps.mp3");
                        Sleep(3000);
                        player.location_id = 2;
                        }
                } else if (choice == 2) {
                    play_sfx("sfx\\crazy.mp3");
                    Sleep(2000);
                    printf("Гул люминесцентных ламп давит на вас с кратной силой! Там слишком страшно...\n");
                    if (player.sanity>50)
                        {player.sanity -= 10;}
                    else
                        {player.sanity -= 50;}
                    printf("Рассудок падает: %d%%\n", player.sanity);
                    if (!has_item(&player, 2)) {
                        Sleep(2000);
                        puts("Словно галлюцинация, из темноты материализуется ключ, который вы тут же хватаете");
                        puts("Еще в коридоре вы оглядывались и его здесь не было.. словно потеря рассудка заставляет это место меняться?..");
                        Sleep(1000);
                        play_sfx("sfx\\pick_up.mp3");
                        add_item(&player, 2, "Ключ от деревянной двери");

                    }
                    system("pause");
                } else if (choice == 3) {
                    puts("Вы возвращаетесь в то место, где вы очнулись..");
                    play_sfx("sfx\\steps.mp3");
                        Sleep(3000);
                        player.location_id = 0;
                } else if (choice == 9) {
                    show_inventory(&player);
                    system("pause");
                } else if (choice == 0) {
                    game_running = 0;
                    game_closed = 1;
                }
                break;
            }

            //3 локация
            case 2: {
                if (player.cutscene_count < 3) {
                    print_ascii_art("locations\\loc3_art0_0.txt", 0);
                    play_sfx("sfx\\loc3_speech.mp3");
                    print_text_typewriter("texts\\loc3_text0_0.txt", 0);
                    player.cutscene_count += 1;
                    system("pause");
                    stop_sfx();
                    }
                else {
                    print_ascii_art("locations\\loc3_art0_0.txt", 1);
                    puts("\nПеред вами кажущиеся бесконечными желтые коридоры.\n");
                }

                const char *actions[] = {
                    "Осмотреть стену перед собой",
                    "Вернуться назад"
                };
                int choice = get_player_choice(actions, 2);

                if (choice == 1) {
                    if(player.sanity > 50)
                        {
                            puts("Просто стена.. возможно, вы еще не настолько потеряли рассудок, чтобы что-либо здесь разглядеть?");
                            system("pause");
                        }
                    else
                        {
                        print_ascii_art("locations\\loc3_art0_1.txt", 0);
                        puts("Прямо на ваших глазах часть стены словно растекается..");
                        Sleep(1000);
                        puts("На стене появляется ослепляющая табличка с надписью \"EXIT\", под ней дверь..");
                        Sleep(1000);
                        puts("Вы осторожно открываете дверь, за ней лестница, в конце почти бесконечного пролета виден яркий белый свет.");
                        play_sfx("sfx\\door2.mp3");
                        Sleep(2000);
                        play_sfx("sfx\\steps1.mp3");
                        system("pause");
                        stop_sfx();
                        game_running = 0;
                        }
                } else if (choice == 2) {
                    puts("Вы возвращаетесь на развилку...");
                    play_sfx("sfx\\steps.mp3");
                        Sleep(3000);
                        player.location_id = 1;
                } else if (choice == 9) {
                    show_inventory(&player);
                    system("pause");
                } else if (choice == 0) {
                    game_running = 0;
                    game_closed = 1;
                }
                break;
            }
        }
    }
    if (player.sanity<=0)
    {
        play_music("background\\death.mp3", 1);
        play_sfx("sfx\\ending2_speech.mp3");
        print_ascii_art("locations\\loc4_art1_0.txt", 0);
        print_text_typewriter("texts\\ending2.txt", 0);
        system("pause");
        stop_sfx();
    }
    else if (player.sanity>0 && game_closed == 0)
    {
        play_music("background\\freedom.mp3", 1);
        play_sfx("sfx\\ending1_speech.mp3");
        print_ascii_art("locations\\loc4_art0_0.txt", 0);
        print_text_typewriter("texts\\ending1.txt", 0);
        system("pause");
        stop_sfx();
    }

    stop_music();

    return 0;
}



