#include <ncursesw/ncurses.h>

void startup();

int main(void)
{
    startup();
    return 0;
}

void startup()
{
    enum
    {
        ERROR = 1,
        SUCCESS = 2,
        WARNING = 3,
        TITLE = 4
    };
    init_pair(ERROR, COLOR_WHITE, COLOR_RED);
    init_pair(SUCCESS, COLOR_WHITE, COLOR_GREEN);
    init_pair(9, COLOR_WHITE, COLOR_YELLOW);
    init_pair(TITLE, COLOR_CYAN, COLOR_BLACK);
    initscr();
    start_color();
    use_default_colors();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    printw("COLORS = %d\n", COLORS);
    printw("COLOR_PAIRS = %d\n", COLOR_PAIRS);
    printw("can_change_color = %d\n", can_change_color());
    attroff(COLOR_PAIR(1));
    if (!(can_change_color())){
        attron(COLOR_PAIR(9));
        printw("Terminal does not support custom colors");
    }

    

    refresh();
    getch();
    endwin();
}
