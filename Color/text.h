/* NIM/Nama     : 13515004/Jordhy Fernando */
/* Tanggal      : 3 November 2016          */
/* File 		: text.h 				   */
/* Deskripsi	: Kumpulan fungsi/prosedur untuk mengatur tampilan text */

#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>

/* Kamus Umum */
#define T_BOLD			 "\033[1m"
#define T_RED     		 "\033[31m"
#define T_GREEN   		 "\033[32m"
#define T_YELLOW  		 "\033[33m"
#define T_BLUE    		 "\033[34m"
#define T_MAGENTA 		 "\033[35m"
#define T_CYAN    		 "\033[36m"
#define T_LIGHT_GRAY 	 "\033[37m"
#define T_DARK_GRAY 	 "\033[90m"
#define T_LIGHT_RED		 "\033[91m"
#define T_LIGHT_GREEN	 "\033[92m"
#define T_LIGHT_YELLOW	 "\033[93m"
#define T_LIGHT_BLUE	 "\033[94m"
#define T_LIGHT_MAGENTA	 "\033[95m"
#define T_LIGHT_CYAN 	 "\033[96m"
#define T_WHITE			 "\033[97m"
#define BG_BLACK		 "\033[40m"
#define BG_RED			 "\033[41m"
#define BG_GREEN		 "\033[42m"
#define BG_YELLOW		 "\033[43m"
#define BG_BLUE			 "\033[44m"
#define BG_MAGENTA		 "\033[45m"
#define BG_CYAN			 "\033[46m"
#define BG_LIGHT_GRAY	 "\033[47m"
#define BG_DARK_GRAY	 "\033[100m"
#define BG_LIGHT_RED	 "\033[101m"
#define BG_LIGHT_GREEN	 "\033[102m"
#define BG_LIGHT_YELLOW	 "\033[103m"
#define BG_LIGHT_BLUE	 "\033[104m"
#define BG_LIGHT_MAGENTA "\033[105m"
#define BG_LIGHT_CYAN	 "\033[106m"
#define BG_WHITE		 "\033[107m"
#define RESET 		 	 "\033[0m"
#define cetakwarna(warnabg, warnatxt, txt) printf(warnabg warnatxt txt RESET "\n")

#endif