/* Numbers written into texts (number_text.h). */
#include "number_text.h"

#include "clean.h"

/* `text` set to the decimal digits of `value`, at most `digits` of them, with three options
 * (all 0 here); whether it worked. */
extern int func_020b45d0(void *text, int value, int digits, int option_a, int option_b, int option_c);

#define NUMBER_TEXT_TWO_DIGITS 2

/* func_020b44a4: `text` set to `value` in at most two digits, plain. */
int NumberText_SetTwoDigits(void *text, int value)
{
    return func_020b45d0(text, value, NUMBER_TEXT_TWO_DIGITS, 0, 0, 0);
}
CLEAN_AS(func_020b44a4, NumberText_SetTwoDigits)

/* func_020b44bc: the same as NumberText_SetTwoDigits; the game has both. */
int NumberText_SetTwoDigitsB(void *text, int value)
{
    return func_020b45d0(text, value, NUMBER_TEXT_TWO_DIGITS, 0, 0, 0);
}
CLEAN_AS(func_020b44bc, NumberText_SetTwoDigitsB)
