#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

#define WIDTH 15
#define HEIGHT 20
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int y;
int x;
int main_board[HEIGHT][WIDTH];
int main_cpy[HEIGHT][WIDTH];
int mblock[4][4];

//--------------Class for Block------------------------------------

class Block
{
public:
    int GetBlockType(int pType, int pRotation, int pX, int pY);
};

char defBlocks[7][4][4][4] =
    {
        // Square
        {
            {{0, 0, 0, 0},
             {0, 1, 1, 0},
             {0, 1, 1, 0},
             {0, 0, 0, 0}},
            {{0, 0, 0, 0},
             {0, 1, 1, 0},
             {0, 1, 1, 0},
             {0, 0, 0, 0}},
            {{0, 0, 0, 0},
             {0, 1, 1, 0},
             {0, 1, 1, 0},
             {0, 0, 0, 0}},
            {{0, 0, 0, 0},
             {0, 1, 1, 0},
             {0, 1, 1, 0},
             {0, 0, 0, 0}}},

        // I
        {
            {{0, 0, 0, 0},
             {1, 1, 1, 1},
             {0, 0, 0, 0},
             {0, 0, 0, 0}},
            {{0, 1, 0, 0},
             {0, 1, 0, 0},
             {0, 1, 0, 0},
             {0, 1, 0, 0}},
            {{0, 0, 0, 0},
             {1, 1, 1, 1},
             {0, 0, 0, 0},
             {0, 0, 0, 0}},
            {
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
            }},
        // L
        {
            {{0, 1, 0, 0},
             {0, 1, 0, 0},
             {0, 1, 1, 0},
             {0, 0, 0, 0}},
            {{0, 0, 0, 0},
             {1, 1, 1, 0},
             {1, 0, 0, 0},
             {0, 0, 0, 0}},
            {{1, 1, 0, 0},
             {0, 1, 0, 0},
             {0, 1, 0, 0},
             {0, 0, 0, 0}},
            {{0, 0, 1, 0},
             {1, 1, 1, 0},
             {0, 0, 0, 0},
             {0, 0, 0, 0}}},
        // L mirrored
        {
            {{0, 1, 0, 0},
             {0, 1, 0, 0},
             {1, 1, 0, 0},
             {0, 0, 0, 0}},
            {{1, 0, 0, 0},
             {1, 1, 1, 0},
             {0, 0, 0, 0},
             {0, 0, 0, 0}},
            {{0, 1, 1, 0},
             {0, 1, 0, 0},
             {0, 1, 0, 0},
             {0, 0, 0, 0}},
            {{0, 0, 0, 0},
             {1, 1, 1, 0},
             {0, 0, 1, 0},
             {0, 0, 0, 0}}},
        // N
        {
            {{0, 0, 1, 0},
             {0, 1, 1, 0},
             {0, 1, 0, 0},
             {0, 0, 0, 0}},
            {{0, 0, 0, 0},
             {1, 1, 0, 0},
             {0, 1, 1, 0},
             {0, 0, 0, 0}},
            {{0, 1, 0, 0},
             {1, 1, 0, 0},
             {1, 0, 0, 0},
             {0, 0, 0, 0}},
            {{1, 1, 0, 0},
             {0, 1, 1, 0},
             {0, 0, 0, 0},
             {0, 0, 0, 0}}},
        // N mirrored
        {
            {{0, 1, 0, 0},
             {0, 1, 1, 0},
             {0, 0, 1, 0},
             {0, 0, 0, 0}},
            {{0, 0, 0, 0},
             {0, 1, 1, 0},
             {1, 1, 0, 0},
             {0, 0, 0, 0}},
            {{1, 0, 0, 0},
             {1, 1, 0, 0},
             {0, 1, 0, 0},
             {0, 0, 0, 0}},
            {{0, 1, 1, 0},
             {1, 1, 0, 0},
             {0, 0, 0, 0},
             {0, 0, 0, 0}}},
        // T
        {
            {{0, 1, 0, 0},
             {0, 1, 1, 0},
             {0, 1, 0, 0},
             {0, 0, 0, 0}},
            {{0, 0, 0, 0},
             {1, 1, 1, 0},
             {0, 1, 0, 0},
             {0, 0, 0, 0}},
            {{0, 1, 0, 0},
             {1, 1, 0, 0},
             {0, 1, 0, 0},
             {0, 0, 0, 0}},
            {{0, 1, 0, 0},
             {1, 1, 1, 0},
             {0, 0, 0, 0},
             {0, 0, 0, 0}}}};
//function to get the required block
int Block::GetBlockType(int pType, int pRotation, int pX, int pY)
{
    return defBlocks[pType][pRotation][pX][pY];
}

//------------------end Block Class-----------------------------

//------------------start Boaed Class---------------------------
//Board Class which holds all the variable and related function
class Board
{

public:
    void control_user_input();
    void save_present_board_to_cpy();
    void processing_block();
    void start();

    void clear_screen();
    void init_draw_main();
    void re_draw_main();
    int getRandom(int min, int max);
    void new_block();
    void move_block(int x, int y);
    void rotate_block();
    void clear_line();
    bool is_collide(int x, int y);
    bool is_game_over();

    enum
    {
        POS_FREE, POS_FILLED, POS_BORDER
    };

private:
    bool isGameOver;
    int score;
};
//determines what should be done with the input
void Board::control_user_input()
{
    char key = getch();
    switch (getch())
    {
    case 'd': //right
        if (!is_collide(x + 1, y))
        {
            move_block(x + 1, y);
        }
        break;
    case 'a': //left
        if (!is_collide(x - 1, y))
        {
            move_block(x - 1, y);
        }
        break;
    case 's': //down
        if (!is_collide(x, y + 1))
        {
            move_block(x, y + 1);
        }
        break;
    case 'w': //rotate
        rotate_block();
    }
}

// copy main_board data to main_cpy before making new block, this will save present data before add new_block.
// when re-draw, below line make new main_board data.
void Board::save_present_board_to_cpy()
{
    for (unsigned int i = 0; i < HEIGHT - 1; i++)
    {
        for (unsigned int j = 0; j < WIDTH - 1; j++)
        {
            main_cpy[i][j] = main_board[i][j];
        }
    }
}
//function to start the game and related process
void Board::start()
{
    unsigned int time_cnt = 0;
    unsigned int WAIT_MAX = 20000;

    while (is_game_over() == false)
    {
        if (kbhit())
        {
            control_user_input();
        }

        if (time_cnt < WAIT_MAX)
        {
            time_cnt++;
        }
        else
        {
            processing_block();
            time_cnt = 0;
        }
    }
    std::cout << "\nScore: " << score << std::endl;
    std::cout << "===============\n"
                 "~~~Game Over~~~\n"
                 "===============\n";

    exit(0);
}
//function to clear screen
void Board::clear_screen()
{
    system("cls");
}
//initialize the board
void Board::init_draw_main()
{

    for (int i = 0; i <= HEIGHT - 2; i++)
    {
        for (int j = 0; j <= WIDTH - 2; j++)
        {
            if ((j == 0) || (j == WIDTH - 2) || (i == HEIGHT - 2))
            {
                main_board[i][j] = POS_BORDER;
                main_cpy[i][j] = POS_BORDER;
            }
            else
            {
                main_board[i][j] = POS_FREE;
                main_cpy[i][j] = POS_FREE;
            }
        }
    }
    new_block();
    re_draw_main();
}
//prints board to console
void Board::re_draw_main()
{
    clear_screen();

    for (unsigned int i = 0; i < HEIGHT - 1; i++)
    {
        for (unsigned int j = 0; j < WIDTH - 1; j++)
        {
            switch (main_board[i][j])
            {
            case POS_FREE: //Empty
                std::cout << " " << std::flush;
                break;
            case POS_FILLED: //Block
                std::cout << "@" << std::flush;
                break;
            case POS_BORDER: //Border
                std::cout << "#" << std::flush;
                break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\nSCORE: " << score << std::endl;
}
//function to generate random number b/w min and max
int Board::getRandom(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
//create a new block and paste onto the board
void Board::new_block()
{
    //initialize coordinates.
    x = 4;
    y = 0;

    Block m;
    int blockType = getRandom(0, 6);
    int rotation = getRandom(0, 3);

    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            mblock[i][j] = POS_FREE;
            mblock[i][j] = m.GetBlockType(blockType, rotation, i, j);
        }
    }

    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            main_board[i][x + j] += mblock[i][j];

            if (main_board[i][x + j] > 1)
            {
                isGameOver = true;
            }
        }
    }
}
//function to move block in 3 directions
void Board::move_block(int x2, int y2)
{
    //Remove block
    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            main_board[y + i][x + j] -= mblock[i][j];
        }
    }

    //update the new coordinate
    x = x2;
    y = y2;

    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            main_board[y + i][x + j] += mblock[i][j];
        }
    }

    re_draw_main();
}
//function to rotate the board
void Board::rotate_block()
{

    int tmp[4][4];

    for (unsigned int i = 0; i < 4; i++)
    { //Save temporarily block
        for (unsigned int j = 0; j < 4; j++)
        {
            tmp[i][j] = mblock[i][j];
        }
    }

    for (unsigned int i = 0; i < 4; i++)
    { //Rotate
        for (unsigned int j = 0; j < 4; j++)
        {
            mblock[i][j] = tmp[3 - j][i];
        }
    }

    if (is_collide(x, y))
    { // And stop if it overlaps not be rotated
        for (unsigned int i = 0; i < 4; i++)
        {
            for (unsigned int j = 0; j < 4; j++)
            {
                mblock[i][j] = tmp[i][j];
            }
        }
    }

    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            main_board[y + i][x + j] -= tmp[i][j];
            main_board[y + i][x + j] += mblock[i][j];
        }
    }

    re_draw_main();
}
//function which handle line detection and update the score
void Board::clear_line()
{
    int count = 0;
    for (int j = 0; j <= HEIGHT - 3; j++)
    {
        int i = 1;
        while (i <= WIDTH - 3)
        {
            if (main_board[j][i] == POS_FREE)
            {
                break;
            }
            i++;
        }

        if (i == WIDTH - 2)
        {
            // Moves all the upper lines one row down
            for (int k = j; k > 0; k--)
            {
                for (int idx = 1; idx <= WIDTH - 3; idx++)
                {
                    main_board[k][idx] = main_board[k - 1][idx];
                }
            }
            count++;
        }
    }
    if (count != 0)
    {
        score += (1 << count) * 100;
    }
}
//check for collision
bool Board::is_collide(int x2, int y2)
{
    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            if (mblock[i][j] && main_cpy[y2 + i][x2 + j] != 0)
            {
                return true;
            }
        }
    }
    return false;
}
//check the value of isGameOver variable
bool Board::is_game_over()
{
    return isGameOver;
}
//save the main_board to main_copy and check the line detection and generate new block if required
void Board::processing_block()
{ //if block can be moved
    if (!is_collide(x, y + 1))
    {
        move_block(x, y + 1);
    }
    else
    { //if block cannot move to down anymore, make a new block.
        clear_line();
        save_present_board_to_cpy();
        new_block();
        re_draw_main();
    }
}

//------end of Board class-----------------------------------------

//-------------main class -----------------------------------------
//runner function
int main()
{

    Board m;

    //initialize coordinates
    x = 4;
    y = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mblock[i][j] = m.POS_FREE;
        }
    }

    //start
    std::cout << "==================\n"
                 "Press 1: Start Game\n"
                 "==================\n";

    int select_num = 0;
    std::cin >> select_num; //get input

    switch (select_num)
    {
    case 1:
        m.clear_screen();   //clear screen
        m.init_draw_main(); //initialize board

        m.start();
        break;
    default:
        exit(0);
        break;
    }
}
//end of main-----------------------------------------------------