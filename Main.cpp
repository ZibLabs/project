#include <ncursesw/ncurses.h>

void setup();
void printHome();

int main(void)
{
    setup();
    printHome();
    refresh();
    getch();
    endwin();
    return 0;
}
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
    ERROR = 10,
    SUCCESS = 11,
    WARNING = 12,
    INFO = 13,
    STANDARD = 14,

};
void setup()
{
    initscr();
    start_color();
    use_default_colors();
    init_pair(ERROR, COLOR_MAGENTA, COLOR_RED);
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
}

void printHome()
{
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            init_pair(ERROR, COLOR_MAGENTA, COLOR_RED);
            init_pair(SUCCESS, COLOR_CYAN, COLOR_GREEN);
            init_pair(1, COLOR_RED, COLOR_YELLOW);
            init_pair(INFO, COLOR_CYAN, COLOR_BLUE);
            init_pair(STANDARD, COLOR_BLACK, COLOR_WHITE);
            init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
            init_pair(RED, COLOR_RED, COLOR_RED);
            init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
            init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
            init_pair(MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
            init_pair(CYAN, COLOR_CYAN, COLOR_CYAN);
            init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
            attron(1);
            printw("g");
            refresh();
        }
    }
}