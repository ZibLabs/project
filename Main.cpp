#include <ncursesw/ncurses.h>
#include <string>
#include <math.h>
#include <ctime>
#include <fstream>

using namespace std;
// function declaration
void setup();
void drawTemplate();
void drawSelected(int selected);
void clearBox();
void execute(int selected);
void game();
void matrix();

int highscore = 0;
// resetMenu allows for a single redrawing when returning rather than repeating it in the while loop
bool resetMenu = true;
bool menuActive = true;
// variable declaration
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
// defines programs
string commandList[3] = {
    "EXIT",   // 0
    "GAME",   // 1
    "MATRIX", // 2
};

// main function
int main(void)
{
    while (menuActive)
    {
        if (resetMenu)
        {
            setup();
            resetMenu = false;
        }
        move(2, 2);
        printw("Pong highscore: %d",
               highscore);
        move(LINES - 5, 2);

        drawSelected(selectNum);
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            selectNum--;
            break;
        case KEY_DOWN:
            selectNum++;
            break;
        case 10:
            execute(selectNum);
            break;
        default:
            break;
        }
        if (selectNum > 2)
        {
            selectNum = 0;
        }
        if (selectNum < 0)
        {
            selectNum = 2;
        }

        clearBox();
        drawSelected(selectNum);
    }
    return 0;
}

// UI functions
void drawSelected(int selected)
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
    noecho();
    leaveok(stdscr, TRUE);
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
    init_pair(111,COLOR_GREEN,COLOR_BLACK);
    drawTemplate();
}

// Clears screen and carves out UI boxes
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
        menuActive = false;
        endwin();
        exit(0);
        break;
    case 1:
        game();
        break;
    case 2:
        matrix();
        break;
    default:
        break;
    }
}
// programs
void game()
{
    srand(time(0));
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
    int score = 0;
    int botFrameLimit = 1000;
    int ballFrameLimit = 500;
    int frame = 0;
    clearBox();
    bool active = true;
    while (active)
    {
        int ch = getch();
        switch (ch)
        {
        case 'q':
            active = false;
            if (score > highscore)
            {
                highscore = score;
            }
            resetMenu = true;
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
        if (frame % botFrameLimit == 0)
        {
            if (ballY > player2y && player2y + 3 < bottom)
            {
                player2y++;
            }
            if (ballY < player2y && player2y - 3 > top)
            {
                player2y--;
            }
        }

        // prints players to screen
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
        if (frame % ballFrameLimit == 0)
        {
            // ball physics
            ballX += ballXVel;
            ballY += ballYVel;
            if (ballY <= top + 1 || ballY >= bottom - 1)
            {
                ballYVel *= -1; // reverse vertical
            }
            if (ballX <= 1)
            {
                ballX = middleX;
                ballY = middleY;
                ballXVel = (rand() % 2 == 0) ? 1 : -1;
                ballYVel = (rand() % 2 == 0) ? 1 : -1;
                ballFrameLimit = 500;
                botFrameLimit += 100;
                if (score > highscore)
                {
                    highscore = score;
                }
                score = 0;
            }
            if (ballX >= boundWidth - 1)
            {
                ballX = middleX;
                ballY = middleY;
                ballXVel = (rand() % 2 == 0) ? 1 : -1;
                ballYVel = (rand() % 2 == 0) ? 1 : -1;
                ballFrameLimit = 500;
                botFrameLimit -= 100;
                score++;
            }
            if (ballX <= 5)
            {
                if (ballY >= player1y - 3 && ballY <= player1y + 3)
                {
                    ballXVel *= -1; // boing
                    ballFrameLimit -= 50;
                }
            }
            if (ballX >= boundWidth - 4)
            {
                if (ballY >= player2y - 3 && ballY <= player2y + 3)
                {
                    ballXVel *= -1; // boing
                    ballFrameLimit -= 50;
                }
            }
        }

        // frame boundchecks
        if (ballFrameLimit < 10)
        {
            ballFrameLimit = 10;
        }
        if (botFrameLimit < 100)
        {
            botFrameLimit = 100;
        }

        frame++;
        // prints ball to screen
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
        move(2, 2);
        printw(
            "Score: %d. q to exit ",
            score);
    }
}
void matrix()
{
    clearBox();
    srand(time(0));
    bool active = true;

    const int NUM_LINE = 50;
    int lineX[NUM_LINE];
    int lineY[NUM_LINE];
    int trailLength[NUM_LINE];
    bool activeLine[NUM_LINE]; // track if the line is currently falling

    // box boundaries
    const int top = 5;
    const int bottom = LINES - 2;
    const int left = 1;
    const int right = COLS - 3; 

    // setup line positions and trails
    for (int i = 0; i < NUM_LINE; i++)
    {
        lineX[i] = left + rand() % (right - left + 1);
        lineY[i] = top;
        trailLength[i] = 3 + rand() % 5;
        activeLine[i] = false;
    }

    nodelay(stdscr, TRUE);

    while (active)
    {
        int ch = getch();
        if (ch == 'q')
        {
            active = false;
            resetMenu = true;
            break;
        }

        for (int i = 0; i < NUM_LINE; i++)
        {
            // randomly activate lines at top
            if (!activeLine[i] && rand() % 100 < 5) // ~5% chance per frame
            {
                activeLine[i] = true;
                lineY[i] = top;
                lineX[i] = left + rand() % (right - left + 1);
                trailLength[i] = 3 + rand() % 5;
            }

            if (activeLine[i])
            {
                // erase tail beyond trail length
                int tailY = lineY[i] - trailLength[i];
                if (tailY >= top)
                {
                    mvaddch(tailY, lineX[i], ' ');
                }

                // draw
                for (int t = 0; t < trailLength[i]; t++)
                {
                    int y = lineY[i] - t;
                    if (y >= top && y <= bottom)
                    {
                        char c = 33 + rand() % 94;
                        attron(COLOR_PAIR(GREEN));
                        mvaddch(y, lineX[i], c);
                        attroff(COLOR_PAIR(GREEN));
                    }
                }

                // move line down
                lineY[i]++;

                // reset if fully past bottom
                if (lineY[i] - trailLength[i] > bottom)
                {
                    activeLine[i] = false;
                }
            }
        }

        move(2, 2);
        printw(
            "Press q to take the red pill and leave the matrix");
        refresh();
        napms(50);
    }

    nodelay(stdscr, FALSE);
}



