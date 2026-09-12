#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    const char *question;
    const char *options[4];
    char answer;
} Question;

static void discard_remaining_input(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) 
     ;   
}

static char read_answer(void)
{
    char input[32];

    for (;;) {
        printf("Your answer (A-D): ");

        if (fgets(input, sizeof(input), stdin) == NULL) 
        {
            return 'Q';
        }

        if (strchr(input, '\n') == NULL) 
        {
            discard_remaining_input();
        }

        if (input[0] != '\0')
         {
            char answer = (char)toupper((unsigned char)input[0]);

            if (answer >= 'A' && answer <= 'D') 
            {
                return answer;
            }
        }

        printf("Invalid choice. Please enter A, B, C, or D.\n");
    }
}

static int play_game(const Question questions[], size_t question_count)
{
    int score = 0;

    for (size_t index = 0; index < question_count; index++)
     {
        printf("\nQuestion %zu of %zu\n%s\n",
               index + 1, question_count, questions[index].question);

        for (int option = 0; option < 4; option++) 
        {
            printf("  %c. %s\n", 'A' + option, questions[index].options[option]);
        }

        char answer = read_answer();
        if (answer == 'Q')
         {
            printf("\nInput ended. Thanks for playing!\n");
            return score;
        }

        if (answer == questions[index].answer)
         {
            printf("Correct!\n");
            score++;
        } else 
        {
            printf("Incorrect. The correct answer was %c.\n",
                   questions[index].answer);
        }
    }

    printf("\nQuiz complete! Your score is %d/%zu.\n", score, question_count);
    if (score == (int)question_count) 
    {
        printf("Excellent work!\n");
    } else if (score >= (int)question_count / 2)
     {
        printf("Good job!\n");
    }
     else
     {
        printf("Keep practicing!\n");
    }

    return score;
}

int main(void)
{
    const Question questions[] = 
    {
        {
            "What is the high level ptograming language?",
            {"php", "html", "python", "c"},
            'C'
        },
        {
            "Which language is primarily used to style web pages?",
            {"HTML", "CSS", "C", "SQL"},
            'B'
        },
        {
            "How many bits are in one byte?",
            {"4", "8", "16", "32"},
            'B'
        },
        {
            "Which planet is known as the Red Planet?",
            {"Venus", "Jupiter", "Mars", "Mercury"},
            'C'
        },
        {
            "What does CPU stand for?",
            {"Central Processing Unit", "Computer Personal Utility",
             "Core Program User", "Central Print Unit"},
            'A'
        }
    };
    const size_t question_count = sizeof(questions) / sizeof(questions[0]);
    char play_again[8];

    printf("================================\n");
    printf("          QUIZ GAME\n");
    printf("================================\n");

    do {
        play_game(questions, question_count);
        printf("\nPlay again? (Y/N): ");

        if (fgets(play_again, sizeof(play_again), stdin) == NULL) 
        {
            break;
        }

        if (strchr(play_again, '\n') == NULL)
         {
            discard_remaining_input();
        }
    } while (toupper((unsigned char)play_again[0]) == 'Y');

    printf("\nThanks for playing!\n");
    return EXIT_SUCCESS;
}