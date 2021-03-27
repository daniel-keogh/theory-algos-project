#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

/* Macros used for printing ANSI coloured terminal output.
 * Reference: <https://www.theurbanpenguin.com/4184-2/>
 */
#define RESET           "\033[0m"
#define RED(s)          "\033[0;31m" s RESET
#define GREEN(s)        "\033[0;32m" s RESET
#define YELLOW(s)       "\033[0;33m" s RESET
#define BLUE(s)         "\033[0;34m" s RESET

#endif
