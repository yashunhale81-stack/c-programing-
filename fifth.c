#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ATTEMPTS 6
#define MAX_INPUT 100

static const char *word_list[] = 
{
	"computer", "programming", "keyboard", "developer", "internet",
	"language", "function", "variable", "compiler", "algorithm"
};

static void display_hangman(int attempts_left)
 {
	static const char *stages[] = 
	{
		"  +---+\n  |   |\n      |\n      |\n      |\n=========",
		"  +---+\n  |   |\n  O   |\n      |\n      |\n=========",
		"  +---+\n  |   |\n  O   |\n  |   |\n      |\n=========",
		"  +---+\n  |   |\n  O   |\n /|   |\n      |\n=========",
		"  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n=========",
		"  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n=========",
		"  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n========="
	};

	printf("\n%s\n", stages[MAX_ATTEMPTS - attempts_left]);
}

static void show_word(const char *word, const int guessed[])
 {
	size_t i;

	printf("Word: ");
	for (i = 0; word[i] != '\0'; i++)
	 {
		if (guessed[(unsigned char) word[i]])
		{
			printf("%c ", word[i]);
		} 
		else
		{
			printf("_ ");
		}
	}
	printf("\n");
}

static int is_word_guessed(const char *word, const int guessed[])
 {
	size_t i;

	for (i = 0; word[i] != '\0'; i++) 
	{
		if (!guessed[(unsigned char) word[i]]) 
		{
			return 0;
		}
	}
	return 1;
}

static void make_lowercase(char *text) 
{
	size_t i;
	for (i = 0; text[i] != '\0'; i++) 
	{
		text[i] = (char) tolower((unsigned char) text[i]);
	}
}

static void trim_newline(char *text)
 {
	text[strcspn(text, "\n")] = '\0';
}

int main(void)
 {
	const size_t word_count = sizeof(word_list) / sizeof(word_list[0]);
	const char *word;
	int guessed[26] = {0};
	int attempts_left = MAX_ATTEMPTS;
	char input[MAX_INPUT];
	int game_won = 0;

	srand((unsigned int) time(NULL));
	word = word_list[rand() % word_count];

	printf("=== HANGMAN GAME ===\n");
	printf("Guess the hidden word one letter at a time.\n");
	printf("You have %d wrong attempts.\n", MAX_ATTEMPTS);

	while (attempts_left > 0 && !game_won)
	{
		int letter;

		display_hangman(attempts_left);
		show_word(word, guessed);
		printf("Wrong attempts remaining: %d\n", attempts_left);
		printf("Enter a letter or guess the whole word: ");

		if (fgets(input, sizeof(input), stdin) == NULL) 
		{
			printf("\nInput ended. Game over.\n");
			return 0;
		}
		trim_newline(input);
		make_lowercase(input);

		if (input[0] == '\0')
		{
			printf("Please enter a letter or word.\n");
			continue;
		}

		if (strlen(input) > 1) 
		{
			if (strcmp(input, word) == 0) 
			{
				game_won = 1;
				break;
			}
			attempts_left--;
			printf("That is not the hidden word.\n");
			continue;
		}

		letter = input[0] - 'a';
		if (letter < 0 || letter >= 26) 
		{
			printf("Please enter an English letter.\n");
			continue;
		}
		if (guessed[letter]) 
		{
			printf("You already guessed '%c'.\n", input[0]);
			continue;
		}

		guessed[letter] = 1;
		if (strchr(word, input[0]) == NULL) 
		{
			attempts_left--;
			printf("Wrong guess.\n");
		} 
		 else 
		{
			printf("Good guess!\n");
		}
		game_won = is_word_guessed(word, guessed);
	}

	if (game_won) 
	{
		printf("\nCongratulations! You guessed the word: %s\n", word);
	} 
	 else 
	{
		display_hangman(0);
		printf("\nGame over! The word was: %s\n", word);
	}

	return 0;
}
