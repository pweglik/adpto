#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY 0
#define BLOCKED 1
#define LINE 2

////// declaration
int width, height;

int success = 0;

int **board;
int **vertical_edges;
int **horizontal_edges;

int start_x = 0;
int start_y = 0;

void draw_board()
{
    for (int i = 0; i < 2 * height + 1; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < 2 * width + 1; j++)
            {
                if (j % 2 == 0)
                {
                    printf(".");
                }
                else
                {
                    if (horizontal_edges[i / 2][(j - 1) / 2] == LINE)
                    {
                        printf("-");
                    }
                    else if (horizontal_edges[i / 2][(j - 1) / 2] == BLOCKED)
                    {
                        printf("x");
                    }
                    else
                    {
                        printf(".");
                    }
                }
            }
        }
        else
        {
            for (int j = 0; j < 2 * width + 1; j++)
            {
                if (j % 2 == 0)
                {
                    if (vertical_edges[(i - 1) / 2][j / 2] == LINE)
                    {
                        printf("|");
                    }
                    else if (vertical_edges[(i - 1) / 2][j / 2] == BLOCKED)
                    {
                        printf("x");
                    }
                    else
                    {
                        printf(".");
                    }
                }
                else
                {
                    printf("%d", board[(i - 1) / 2][(j - 1) / 2]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool verify_solution()
{
    int x = -1;
    int y = -1;
    // loop over horizontal lines until we find one.
    // start from left point and go right
    for (int i = 0; i < height + 1; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (horizontal_edges[i][j] == LINE)
            {
                y = i;
                x = j + 1;
                goto looping;
            }
        }
    }

    if (x == -1 && y == -1)
    {
        return false;
    }

looping:
    start_x = x - 1;
    start_y = y;

    int prev_x = start_x;
    int prev_y = start_y;

    while (start_x != x || start_y != y)
    {
        // move from x, y

        if (vertical_edges[y - 1][x] == LINE && prev_y != y - 1)
        { // up
            prev_y = y;
            y = y - 1;
        }
        else if (horizontal_edges[y][x] == LINE && prev_x != x + 1)
        { // right
            prev_x = x;
            x = x + 1;
        }
        else if (vertical_edges[y][x] == LINE && prev_y != y + 1)
        { // down
            prev_y = y;
            y = y + 1;
        }
        else if (horizontal_edges[y][x - 1] && prev_x != x - 1)
        { // left
            prev_x = x;
            x = x - 1;
        }
        else
        { // no way forward
            return false;
        }
    }

    return true;
}

void mask_to_board(u_int64_t mask)
{
    for (int i = 0; i < width * (height + 1) + (width + 1) * height; i++)
    {
        int value = (mask >> i) & 1;
        if (i < width * (height + 1))
        {
            if (value == 1)
            {
                vertical_edges[i / (width + 1)][i % (width + 1)] = LINE;
            }
            else
            {
                vertical_edges[i / (width + 1)][i % (width + 1)] = EMPTY;
            }
        }
        else
        {
            int temp = i - width * (height + 1);
            if (value == 1)
            {
                horizontal_edges[temp / width][temp % width] = LINE;
            }
            else
            {
                horizontal_edges[temp / width][temp % width] = EMPTY;
            }
        }
    }
}

int main()
{
    ////// Initialization
    board = (int **)malloc(height * sizeof(int *));
    vertical_edges = (int **)malloc((height) * sizeof(int *));
    horizontal_edges = (int **)malloc((height + 1) * sizeof(int *));

    ////// Input
    scanf("%d %d", &width, &height);
    for (int i = 0; i < height; i++)
    {
        board[i] = (int *)calloc(width, sizeof(int));
        vertical_edges[i] = (int *)calloc(width + 1, sizeof(int));
        horizontal_edges[i] = (int *)calloc(width, sizeof(int));

        for (int j = 0; j < width; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    horizontal_edges[height] = (int *)calloc(width + 1, sizeof(int));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    draw_board();
    printf("drew!\n");
    //  brute force
    for (u_int64_t mask = 0; mask < 20; mask++)
    // 1 << (width * (height + 1) + (width + 1) * height + 1); mask++)
    {
        mask_to_board(mask);
        bool succes = verify_solution();
        // printf("%llu\n", mask);
        // draw_board();
        if (succes)
        {
            printf("success!! %llu\n", mask);
            break;
        }
    }
    draw_board();
    ////// Freeing memory
    // for (int i = 0; i < height; i++)
    // {
    //     free(board[i]);
    //     free(vertical_edges[i]);
    //     free(horizontal_edges[i]);
    // }
    // free(horizontal_edges[height]);
    // free(board);
    // free(vertical_edges);
    // free(horizontal_edges);
}