#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define BLOCKED 1
#define LINE 2

////// declaration
int width, height;

int **board;
int **vertical_edges;
int **horizontal_edges;

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
}

void fill_corners()
{
    // 0s
    if (board[0][0] == 0)
    {
        vertical_edges[0][0] = BLOCKED;
        vertical_edges[0][1] = BLOCKED;
        horizontal_edges[0][0] = BLOCKED;
        horizontal_edges[1][0] = BLOCKED;
    }
    if (board[height - 1][0] == 0)
    {
        vertical_edges[height - 1][0] = BLOCKED;
        vertical_edges[height - 1][1] = BLOCKED;
        horizontal_edges[height - 1][0] = BLOCKED;
        horizontal_edges[height][0] = BLOCKED;
    }
    if (board[0][width - 1] == 0)
    {
        vertical_edges[0][width - 1] = BLOCKED;
        vertical_edges[0][width] = BLOCKED;
        horizontal_edges[0][width - 1] = BLOCKED;
        horizontal_edges[1][width - 1] = BLOCKED;
    }
    if (board[height - 1][width - 1] == 0)
    {
        vertical_edges[width - 1][height - 1] = BLOCKED;
        vertical_edges[width - 1][height] = BLOCKED;
        horizontal_edges[width - 1][height - 1] = BLOCKED;
        horizontal_edges[width][height - 1] = BLOCKED;
    }
    // 1s
    if (board[0][0] == 1)
    {
        vertical_edges[0][0] = BLOCKED;
        horizontal_edges[0][0] = BLOCKED;
    }
    if (board[height - 1][0] == 1)
    {
        vertical_edges[height - 1][0] = BLOCKED;
        horizontal_edges[height][0] = BLOCKED;
    }
    if (board[0][width - 1] == 1)
    {
        vertical_edges[0][width] = BLOCKED;
        horizontal_edges[0][width - 1] = BLOCKED;
    }
    if (board[height - 1][width - 1] == 1)
    {
        vertical_edges[height - 1][width] = BLOCKED;
        horizontal_edges[height][width - 1] = BLOCKED;
    }
    // 2s
    if (board[0][0] == 2)
    {
        vertical_edges[1][0] = LINE;
        horizontal_edges[0][1] = LINE;
    }
    if (board[height - 1][0] == 2)
    {
        vertical_edges[height - 2][0] = LINE;
        horizontal_edges[height][1] = LINE;
    }
    if (board[0][width - 1] == 2)
    {
        vertical_edges[1][width] = LINE;
        horizontal_edges[0][width - 2] = LINE;
    }
    if (board[height - 1][width - 1] == 2)
    {
        vertical_edges[width - 2][height] = LINE;
        horizontal_edges[width][height - 2] = LINE;
    }
    // 3s
    if (board[0][0] == 3)
    {
        vertical_edges[0][0] = LINE;
        horizontal_edges[0][0] = LINE;
    }
    if (board[height - 1][0] == 3)
    {
        vertical_edges[height - 1][0] = LINE;
        horizontal_edges[height][0] = LINE;
    }
    if (board[0][width - 1] == 3)
    {
        vertical_edges[0][width] = LINE;
        horizontal_edges[0][width - 1] = LINE;
    }
    if (board[height - 1][width - 1] == 3)
    {
        vertical_edges[width - 1][height] = LINE;
        horizontal_edges[width][height - 1] = LINE;
    }
}

int main()
{
    ////// Initialization
    board = (int **)malloc(height * sizeof(int *));
    vertical_edges = (int **)malloc((height + 1) * sizeof(int *));
    horizontal_edges = (int **)malloc((height + 1) * sizeof(int *));

    ////// Input
    scanf("%d %d", &width, &height);
    for (int i = 0; i < height; i++)
    {
        board[i] = (int *)malloc(width * sizeof(int));
        vertical_edges[i] = (int *)calloc(width + 1, sizeof(int));
        horizontal_edges[i] = (int *)calloc(width + 1, sizeof(int));

        for (int j = 0; j < width; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    vertical_edges[height] = (int *)calloc(width + 1, sizeof(int));
    horizontal_edges[height] = (int *)calloc(width + 1, sizeof(int));

    ////// Initial information
    // Corners
    fill_corners();

    // Block 0s
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (board[i][j] == 0)
            {
                vertical_edges[i][j] = BLOCKED;
                vertical_edges[i][j + 1] = BLOCKED;
                horizontal_edges[i][j] = BLOCKED;
                horizontal_edges[i + 1][j] = BLOCKED;
            }
        }
    }
    // Adjecent 0 and 3

    // Diagonal 0 and 3

    // Two adjecent 3s

    // Two diagonal 3s

    ////// Main Loop
    //// Basic techniques

    draw_board();
    ////// Freeing memory
    for (int i = 0; i < height; i++)
    {
        free(board[i]);
        free(vertical_edges[i]);
        free(horizontal_edges[i]);
    }
    // free(vertical_edges[height]);
    // free(horizontal_edges[height]);
    // free(board);
    // free(vertical_edges);
    // free(horizontal_edges);
}