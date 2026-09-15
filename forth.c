#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
extern FILE *_popen(const char *command, const char *mode);
extern int _pclose(FILE *pipe);
#define popen _popen
#define pclose _pclose
#endif

typedef struct {
	const char *code;
	const char *name;
	double per_usd;
} Currency;

typedef struct {
	double amount;
	double converted_amount;
	int from;
	int to;
	time_t timestamp;
} ConversionRecord;

static Currency currencies[] = {
	{"USD", "US Dollar", 1.0},
	{"GBP", "British Pound", 0.79},
	{"INR", "Indian Rupee", 83.10},
	{"JPY", "Japanese Yen", 149.50},
	{"BRL", "Brazilian Real", 5.45}
};

static const int currency_count = sizeof(currencies) / sizeof(currencies[0]);
static const int max_history = 20;

static int load_live_rates(void) {
	const char *command =
		"curl -fsS --max-time 10 "
		"https://api.frankfurter.dev/v1/latest?base=USD";
	const char *rate_codes[] = {"GBP", "INR", "JPY", "BRL"};
	char response[16384];
	FILE *pipe;
	size_t length = 0;
	int i;

	pipe = popen(command, "r");
	if (pipe == NULL) {
		return 0;
	}

	while (length < sizeof(response) - 1 &&
		   fgets(response + length, (int)(sizeof(response) - length), pipe) != NULL) {
		length = strlen(response);
	}
	response[length] = '\0';
	pclose(pipe);

	for (i = 0; i < 4; i++) {
		char key[16];
		char *rate_text;
		double rate;

		snprintf(key, sizeof(key), "\"%s\":", rate_codes[i]);
		rate_text = strstr(response, key);
		if (rate_text == NULL || sscanf(rate_text + strlen(key), "%lf", &rate) != 1) {
			return 0;
		}
		currencies[i + 1].per_usd = rate;
	}

	return 1;
}

static void show_currencies(void) {
	int i;

	printf("\nAvailable currencies:\n");
	for (i = 0; i < currency_count; i++) {
		printf("%d. %s - %s\n", i + 1, currencies[i].code,
			   currencies[i].name);
	}
}

static int read_currency_choice(const char *prompt) {
	int choice;

	printf("%s", prompt);
	if (scanf("%d", &choice) != 1 || choice < 1 || choice > currency_count) {
		while (getchar() != '\n' && !feof(stdin)) {
		}
		return -1;
	}

	return choice - 1;
}

static void show_history(const ConversionRecord history[], int history_count) {
	int i;

	printf("\nConversion History:\n");
	if (history_count == 0) {
		printf("No conversions yet.\n");
		return;
	}

	for (i = 0; i < history_count; i++) {
		char timestamp[32];
		struct tm *time_info = localtime(&history[i].timestamp);

		if (time_info != NULL) {
			strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);
		} else {
			strcpy(timestamp, "Unknown time");
		}

		printf("%d. [%s] %.2f %s = %.2f %s\n", i + 1, timestamp,
			   history[i].amount, currencies[history[i].from].code,
			   history[i].converted_amount, currencies[history[i].to].code);
	}
}

int main(void) {
	double amount;
	double converted_amount;
	int from;
	int to;
	char again;
	int live_rates_loaded;
	ConversionRecord history[20];
	int history_count = 0;

	printf("=== Currency Converter ===\n");
	live_rates_loaded = load_live_rates();
	if (live_rates_loaded) {
		printf("Live exchange rates loaded successfully.\n");
	} else {
		printf("Live rates unavailable. Using sample rates.\n");
	}

	do {
		show_currencies();

		from = read_currency_choice("Convert from (number): ");
		to = read_currency_choice("Convert to (number): ");

		if (from == -1 || to == -1) {
			printf("Invalid currency choice. Please try again.\n");
		} else {
			printf("Enter amount in %s: ", currencies[from].code);
			if (scanf("%lf", &amount) != 1 || amount < 0) {
				while (getchar() != '\n' && !feof(stdin)) {
				}
				printf("Invalid amount. Please enter a non-negative number.\n");
			} else {
				converted_amount = amount * currencies[to].per_usd /
								   currencies[from].per_usd;
				printf("%.2f %s = %.2f %s\n", amount, currencies[from].code,
					   converted_amount, currencies[to].code);

				if (history_count == max_history) {
					memmove(history, history + 1,
							(sizeof(history[0]) * (max_history - 1)));
					history_count--;
				}
				history[history_count].amount = amount;
				history[history_count].converted_amount = converted_amount;
				history[history_count].from = from;
				history[history_count].to = to;
				history[history_count].timestamp = time(NULL);
				history_count++;
				show_history(history, history_count);
			}
		}

		printf("\nDo another conversion? (y/n): ");
		scanf(" %c", &again);
	} while (again == 'y' || again == 'Y');

	printf("Thank you for using the currency converter.\n");
	return 0;
}
