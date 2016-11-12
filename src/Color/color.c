#include <stdio.h>

#define TEXT_BOLD			"\033[1m"
#define TEXT_RED     		"\033[31m"
#define TEXT_GREEN   		"\033[32m"
#define TEXt_YELLOW  		"\033[33m"
#define TEXT_BLUE    		"\033[34m"
#define TEXT_MAGENTA 		"\033[35m"
#define TEXT_CYAN    		"\033[36m"
#define TEXT_LIGHT_GRAY 	"\033[37m"
#define TEXT_DARK_GRAY 		"\033[90m"
#define TEXT_LIGHT_RED		"\033[91m"
#define TEXT_LIGHT_GREEN	"\033[92m"
#define TEXT_LIGHT_YELLOW	"\033[93m"
#define TEXT_LIGHT_BLUE		"\033[94m"
#define TEXT_LIGHT_MAGENTA	"\033[95m"
#define TEXT_LIGHT_CYAN 	"\033[96m"
#define TEXT_WHITE			"\033[97m"
#define BACK_BLACK			"\033[40m"
#define BACK_RED			"\033[41m"
#define BACK_GREEN			"\033[42m"
#define BACK_YELLOW			"\033[43m"
#define BACK_BLUE			"\033[44m"
#define BACK_MAGENTA		"\033[45m"
#define BACK_CYAN			"\033[46m"
#define BACK_LIGHT_GRAY		"\033[47m"
#define BACK_DARK_GRAY		"\033[100m"
#define BACK_LIGHT_RED		"\033[101m"
#define BACK_LIGHT_GREEN	"\033[102m"
#define BACK_LIGHT_YELLOW	"\033[103m"
#define BACK_LIGHT_BLUE		"\033[104m"
#define BACK_LIGHT_MAGENTA	"\033[105m"
#define BACK_LIGHT_CYAN		"\033[106m"
#define BACK_WHITE			"\033[107m"
#define RESET 		 		"\033[0m"

#define printcolor(x,color) printf(color x ANSI_COLOR_RESET "\n");


int main (int argc, char const *argv[]) {

  printcolor("This text is BLUE", ANSI_COLOR_BLUE);
  printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");

  return 0;
}