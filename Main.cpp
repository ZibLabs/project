#include <ncursesw/ncurses.h>
#include <string>
using namespace std;
// function declaration
void setup();
void drawTemplate();
void programSelect(int selected);
void clearBox();
void execute(int selected);
void game();
void clock();
void typewriter();
void calibrate();
// variable declaration
bool active = true;
int selectNum = 0;
enum
{

    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7,
    FAIL = 10,
    SUCCESS = 11,
    WARNING = 12,
    INFO = 13,
    STANDARD = 14,
    SELECTED = 15,

};
string commandList[5] = {
    "EXIT", //0
    "GAME", //1
    "CLOCK", //2
    "TYPEWRITER", //3
    "SIZE CALIBRATION TOOL"}; //4

// defines programs 
// main function
int main(void)
{
    setup();
    move(2, 2);
    printw("Welcome to unnamed terminal UI I made");
    while (active)
    {
        move(LINES - 5, 2);

        programSelect(selectNum);
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            selectNum += 1;
            break;
        case KEY_DOWN:
            selectNum -= 1;
            break;
        case 10:
            execute(selectNum);
        default:
            break;
        }
        if (selectNum > 4)
        {
            selectNum = 0;
        }
        if (selectNum < 0)
        {
            selectNum = 4;
        }

        clearBox();
        programSelect(selectNum);
    }
    return 0;
}

// UI functions
void programSelect(int selected)
{
    move(LINES - 4, 2);
    string buffer = commandList[selected];
    attron(COLOR_PAIR(SELECTED));
    printw("%s", buffer.c_str());
    attroff(COLOR_PAIR(SELECTED));
    refresh();
}

void setup()
{
    initscr();
    start_color();
    use_default_colors();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    init_pair(FAIL, COLOR_MAGENTA, COLOR_RED);
    init_pair(SUCCESS, COLOR_CYAN, COLOR_GREEN);
    init_pair(WARNING, COLOR_RED, COLOR_YELLOW);
    init_pair(INFO, COLOR_CYAN, COLOR_BLUE);
    init_pair(STANDARD, COLOR_BLACK, COLOR_WHITE);
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_RED);
    init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(CYAN, COLOR_CYAN, COLOR_CYAN);
    init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
    init_pair(SELECTED, COLOR_BLACK, COLOR_CYAN);
    drawTemplate();
}

void drawTemplate()
{
    for (int y = 0; y < LINES; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            attron(COLOR_PAIR(WHITE));
            printw(" ");
            attroff(COLOR_PAIR(WHITE));
        }
    }

    for (int y = 1; y < 4; y++)
    {
        move(y, 1);
        for (int x = 0; x < COLS - 2; x++)
        {
            attron(COLOR_PAIR(BLACK));
            printw(" ");
            attroff(COLOR_PAIR(BLACK));
        }
    }
    clearBox();
    refresh();
}

void clearBox()
{
    for (int y = 5; y < LINES - 1; y++)
    {
        move(y, 1);
        for (int x = 0; x < COLS - 2; x++)
        {
            attron(COLOR_PAIR(BLACK));
            printw(" ");
            attroff(COLOR_PAIR(BLACK));
        }
    }
}

// selects and runs func for program
void execute(int selected){
    switch (selected)
    {
    case 0:
        endwin();
        exit(0);
        break;
    case 1:
        game();
        break;
    
    default:
        printw("Not implimented yet");
        break;
    }
}
// programs
void game(){
    clearBox();
}