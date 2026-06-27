// game-snake.cpp : A small cross-platform console Snake game.
// Program execution begins and ends in main().

#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

using namespace std;

#pragma region Platform helpers

// Returns true if a key is currently waiting in the input buffer.
static bool keyHit() {
#ifdef _WIN32
    return _kbhit();
#else
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
#endif
}

// Reads a single character without waiting for Enter.
static int readKey() {
#ifdef _WIN32
    return _getch();
#else
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

// Clears the terminal screen.
static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // ANSI: move cursor to home and clear screen.
    cout << "\033[2J\033[H";
#endif
}

// Sleeps for the given number of milliseconds.
static void sleepMs(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

#pragma endregion

#pragma region Game state

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

#pragma endregion

// Places a fruit on a random free cell inside the playing field.
void SpawnFruit() {
    fruitX = rand() % width;
    fruitY = rand() % height;
}

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    nTail = 0;
    score = 0;
    SpawnFruit();
}

void Draw() {
    clearScreen();

    // Top wall.
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << "\n";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; // left wall

            if (i == y && j == x)
                cout << "O"; // snake head
            else if (i == fruitY && j == fruitX)
                cout << "F"; // fruit
            else {
                bool printed = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // snake body
                        printed = true;
                        break;
                    }
                }
                if (!printed)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#"; // right wall
        }
        cout << "\n";
    }

    // Bottom wall.
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << "\n";

    cout << "SCORE: " << score << "\n";
    cout << "Controls: W/A/S/D to move, X to quit\n";
}

void Input() {
    if (keyHit()) {
        switch (readKey()) {
        case 'a': case 'A':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd': case 'D':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w': case 'W':
            if (dir != DOWN) dir = UP;
            break;
        case 's': case 'S':
            if (dir != UP) dir = DOWN;
            break;
        case 'x': case 'X':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    // Shift the tail so each segment follows the one in front of it.
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    default: break;
    }

    // Hitting a wall ends the game.
    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    // Running into your own tail ends the game.
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // Eating the fruit grows the snake and respawns the fruit.
    if (x == fruitX && y == fruitY) {
        score += 10;
        nTail++;
        SpawnFruit();
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        sleepMs(150);
    }

    clearScreen();
    cout << "Game over! Final score: " << score << "\n";
    return 0;
}
