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
    "EXIT",                   // 0
    "GAME",                   // 1
    "CLOCK",                  // 2
    "TYPEWRITER",             // 3
    "SIZE CALIBRATION TOOL"}; // 4

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
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    init_pair(FAIL, COLOR_MAGENTA, COLOR_RED);
    init_pair(SUCCESS, COLOR_CYAN, COLOR_GREEN);
    init_pair(WARNING, COLOR_RED, COLOR_YELLOW);
    init_pair(INFO, COLOR_CYAN, COLOR_BLUE);
    init_pair(STANDARD, COLOR_BLACK, COLOR_WHITE);
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_RED);
    init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
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
void execute(int selected)
{
    switch (selected)
    {
    case 0:
        endwin();
        exit(0);
        break;
    case 1:
        game();
        break;
    case 4:
        calibrate();
        break;
    default:
        printw("Not implimented yet");
        break;
    }
}
// programs
void game()
{
    int top = 5;
    int bottom = LINES - 2;
    int player1y = (top + bottom) / 2;
    int player2y = (top + bottom) / 2;
    int boundWidth = COLS - 2;
    int boundHeight = bottom - top;
    int middleX = COLS / 2;
    int middleY = (top + bottom) / 2;
    int ballX = middleX;
    int ballY = middleY;
    int ballXVel = (rand() % 2 == 0) ? 1 : -1;
    int ballYVel = (rand() % 2 == 0) ? 1 : -1;

    int frameLimit = 500;
    int frame = 0;
    clearBox();
    bool active = true;
    while (active)
    {
        // calculations and input
        int ch = getch();
        switch (ch)
        {
        case 'q':
            active = false;
            break;
        case KEY_UP:
            if (player1y - 3 > top)
            {
                player1y--;
            }
            break;
        case KEY_DOWN:
            if (player1y + 3 < bottom)
            {
                player1y++;
            }
            break;
        }
        clearBox();

        // printing all details to user
        attron(COLOR_PAIR(YELLOW));
        for (int y = -3; y <= 3; y++)
        {
            move(player1y + y, 2);
            printw("  ");
        }
        attroff(COLOR_PAIR(YELLOW));

        attron(COLOR_PAIR(YELLOW));
        for (int y = -3; y <= 3; y++)
        {
            move(player2y + y, COLS - 4);
            printw("  ");
        }
        attroff(COLOR_PAIR(YELLOW));

        


        for (int y = 0; y < boundHeight + 1; y++)
        {
            move(top + y, COLS / 2);
            printw("|");
        }
        // frame limiter for ball phyisics
        if (frame >= frameLimit)
        {
            // ball physics
            ballX += ballXVel;
            ballY += ballYVel;
            if (ballY <= top + 1 || ballY >= bottom - 1)
            {
                ballYVel *= -1; // reverse vertical direction
            }
            if (ballX <= 1 || ballX >= boundWidth)
            {
                ballXVel *= -1; // reverse horizontal direction
            }
            frame = 0;
            if (ballX <= 5)
            {
                if (ballY >= player1y - 3 && ballY <= player1y + 3)
                {
                    ballXVel *= -1; // boing
                    frameLimit -= 10;
                }
            }
        }
        frame++;
        attron(COLOR_PAIR(CYAN));
        for (int y = -1; y <= 1; y++)
        {
            for (int x = -1; x <= 1; x++)
            {
                move(ballY + y, ballX + x);
                printw(" ");
            }
        }
        attroff(COLOR_PAIR(CYAN));
    }
}
void calibrate()
{
}
