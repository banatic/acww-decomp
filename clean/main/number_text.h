/* Numbers written into texts (func_020b45d0: a text set to a number's digits, with options),
 * and two entry points the talks use for a number of at most two digits. */
#ifndef CLEAN_MAIN_NUMBER_TEXT_H
#define CLEAN_MAIN_NUMBER_TEXT_H

int NumberText_SetTwoDigits(void *text, int value);
int NumberText_SetTwoDigitsB(void *text, int value);

/* The rest of the number texts: the formatter (NumberText_Format) and its steps, the unit word
 * after a number (NumberText_AppendUnit) and a fixed-point number (NumberText_SetFixed).
 *
 * The formatter builds the digits in a work buffer of 2-byte characters, high byte first and
 * the least significant digit first, pads them, then reverses the bytes, which leaves a text of
 * little-endian 16-bit characters with the most significant digit first. */
#include "types.h"

/* The formats NumberText_Format takes. An odd format also asks for commas between groups of
 * three digits (NumberText_InsertCommas), which never appear: see there. */
enum NumberTextFormat {
    NUMBER_TEXT_PLAIN = 0,
    NUMBER_TEXT_COMMAS = 1,
    NUMBER_TEXT_LEFT = 2, /* padded with spaces after the digits */
    NUMBER_TEXT_LEFT_COMMAS = 3,
    NUMBER_TEXT_RIGHT = 4, /* padded with spaces before the digits */
    NUMBER_TEXT_RIGHT_COMMAS = 5,
    NUMBER_TEXT_ZEROS = 6, /* padded with zeros before the digits */
    NUMBER_TEXT_ZEROS_COMMAS = 7
};

int NumberText_SetFixed(void *text, s32 value, int decimals);
int NumberText_Format(void *text, int value, int digits, int format, int unit, u8 half_width);
int NumberText_AppendUnit(void *text, int value, int unit);
void NumberText_ToFullWidth(char *dst, unsigned int dst_size, const char *src, unsigned int src_size);
void NumberText_Reverse(signed char *work, unsigned int size);
void NumberText_InsertCommas(char *work, unsigned int size, int group);
void NumberText_PadZeros(char *work, int size, int digits);
void NumberText_PadSpacesBefore(unsigned char *work, int size, int digits);
void NumberText_PadSpacesAfter(unsigned char *work, u32 size, int digits);
void NumberText_WriteDigits(char *work, int size, int value, int digits);
void NumberText_MoveUp(signed char *bytes, int end, int start, int distance);
int NumberText_LengthFrom(char *work, unsigned int size, int unused, unsigned int at);

#endif
