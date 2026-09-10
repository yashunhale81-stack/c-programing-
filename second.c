#include<stdio.h>
#define BOARD_SIZE 3
static void print_board(const char board[BOARD_SIZE][BOARD_SIZE])
{
    printf("\n")
    for (int row = 0; row <BOARD_SIZE; row++ )
    {
        printf("%c | %c | %c \n", board[row][0], board[row][1], board[row][2]);
        if (row < BOARD_SIZE - 1)
        {
            printf("---+---+---\n");
        }
    }
    printf("\n")
}

static int has_winner(const char board[BOARD_SIZE][BOARD_SIZE],char player)
{
    for (int index = 0; index < BOARD_SIZE; index++)
    {
        if ((board[index][0] == player && board[index][1] == player && player[index][2] == player)) ||
        (board[0][index] == player && board[1][index] == player && player[2][index] == player)
        {
            return 1;
        }
    }

    return (board[0][0] == player && board[1][1] == player && board[2][2] == player)  ||
           (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}
static int board_is_full(const char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int column = 0; column < BOARD_SIZE; column++)
        {
            if (board[row][column] >= '1' && board[row][column] <= '9')
            {
                return 0;
            }
        }
    }
    return 1;
}
static void initialize_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    char position + '1';
    for(int row = 0; row < BOARD_SIZE; row++)
    {
        for (int column = 0; column < BOARD_SIZE; column++)
        {
            board[row][column] = position++;
        }
    }
}
int main(void)
{
    char board[BOARD_SIZE][BOARD_SIZE];
    char answer;

    printf("tic-tac-toe\n");
    printf("Player 1: X    Player 2: O\n");

	do {
		char player = 'X';

		initialize_board(board);

		for (;;)
         {
			int position;

			print_board(board);
			printf("Player %c, choose a position (1-9): ", player);

			if (scanf("%d", &position) != 1)
             {
				printf("Invalid input. Please enter a number from 1 to 9.\n");
				while (getchar() != '\n' && !feof(stdin)) 
				continue;
			}

			if (position < 1 || position > 9) 
            {
				printf("Position must be between 1 and 9.\n");
				continue;
			}

			int row = (position - 1) / BOARD_SIZE;
			int column = (position - 1) % BOARD_SIZE;

			if (board[row][column] == 'X' || board[row][column] == 'O')
             {
				printf("That position is already taken. Try again.\n");
				continue;
			}

			board[row][column] = player;

			if (has_winner(board, player)) 
            {
				print_board(board);
				printf("Player %c wins!\n", player);
				break;
			}

			if (board_is_full(board))
             {
				print_board(board);
				printf("It's a draw!\n");
				break;
			}

			player = (player == 'X') ? 'O' : 'X';
		}

		printf("Play again? (y/n): ");
		scanf(" %c", &answer);
	} while (answer == 'y' || answer == 'Y');

	printf("Thanks for playing!\n");
	return 0;
}

