/* Numbers written into texts (func_020b45d0: a text set to a number's digits, with options),
 * and two entry points the talks use for a number of at most two digits. */
#ifndef CLEAN_MAIN_NUMBER_TEXT_H
#define CLEAN_MAIN_NUMBER_TEXT_H

int NumberText_SetTwoDigits(void *text, int value);
int NumberText_SetTwoDigitsB(void *text, int value);

#endif
