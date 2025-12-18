#include <ncursesw/ncurses.h>
#include <windows.h>

void setup();
void drawTemplate();

int main(void)
{
    setup();
    
    move(2,2);
    printw("Welcome to unnamed terminal UI I made");
    refresh();
    Sleep(5000);
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
    FAIL = 10,
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
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
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
            refresh();
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
            refresh();
            attroff(COLOR_PAIR(BLACK));
        }
    }
    for (int y = 5; y < LINES-1; y++)
    {
        move(y, 1);
        for (int x = 0; x < COLS - 2; x++)
        {
            attron(COLOR_PAIR(BLACK));
            printw(" ");
            refresh();
            attroff(COLOR_PAIR(BLACK));
        }
    }
}