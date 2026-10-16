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

/* The formatter's work buffer, its full-width copy, and the texts NumberText_SetFixed uses. */
#define NUMBER_TEXT_WORK_SIZE 0x1c
#define NUMBER_TEXT_WIDE_SIZE 0x1e
#define NUMBER_TEXT_DIGITS_MAX 10
#define NUMBER_TEXT_COMMA_GROUP 3
#define NUMBER_TEXT_FX_SHIFT 12

/* A number text (0x40 bytes, func_020b5630 builds it) and a message part (0x5c bytes,
 * func_020a8228 builds it). */
typedef struct NumberTextBuffer {
    u8 bytes[0x40];
} NumberTextBuffer;
typedef struct NumberTextPart {
    u8 bytes[0x5c];
} NumberTextPart;

extern s32 FX_Modf(s32 value, s32 *integer); /* the fraction; the integer part in *integer */
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void *func_020b5630(NumberTextBuffer *text);
extern void *func_020b5618(NumberTextBuffer *text);
extern void *func_020a8228(NumberTextPart *part);
extern void *func_020a8210(NumberTextPart *part);
/* Texts: set from another text, appended raw characters, appended another text, set from raw
 * characters; each says whether it worked. */
extern int func_020a8bb8(void *text, const void *source);
extern int func_020a89f8(void *text, const void *characters);
extern int func_020a89dc(void *text, const void *source);
extern int func_020a8be4(void *text, const void *characters);
/* Message *message of the group `group` (in "/script/KOR/string") read into `text`. */
extern int func_020b4a20(void *text, u8 *message, const char *group);
/* The bytes before the first 0x0000 character of a text, at most `size`. */
extern int func_020b4950_unk(const void *text, unsigned int size);

extern const char data_020d2080[];   /* "." in 16-bit characters */
extern const u8 data_020d2094[10];   /* the unit messages by last digit, unit 6 */
extern const u8 data_020d20a0[10];   /* the same for unit 9 */
extern const u8 data_020d20ac[10];   /* the same for unit 3 */
extern const char data_020e5300[];   /* "st_unit" */
extern const char data_020d2078[2];  /* the full-width space (0x3000), high byte first */
extern const char data_020d207c[2];  /* the full-width comma (0xff0c), likewise */
extern const char data_020d20b8[20]; /* the full-width digits (0xff10-0xff19), likewise */

/* func_020b4508: `text` set to the fixed-point (20.12) number `value` as "<integer>.<fraction>"
 * with `decimals` digits of fraction; whether every step worked. QUIRK: the fraction is
 * written as a plain number, so its leading zeros are lost (0.05 with two decimals gives
 * "0.5"). QUIRK: a message part is built and destroyed around it without being used. */
int NumberText_SetFixed(void *text, s32 value, int decimals)
{
    NumberTextBuffer integer_text;
    NumberTextBuffer fraction_text;
    NumberTextPart unused;
    s32 integer;
    s32 fraction = FX_Modf(value, &integer);

    for (int i = 0; i < decimals; i++) {
        fraction *= 10;
    }
    func_020b5630(&integer_text);
    func_020b5630(&fraction_text);
    func_020a8228(&unused);
    int ok = NumberText_Format(&integer_text, integer >> NUMBER_TEXT_FX_SHIFT, NUMBER_TEXT_DIGITS_MAX, 0, 0, 0) & 1;
    ok = (ok & NumberText_Format(&fraction_text, fraction >> NUMBER_TEXT_FX_SHIFT, NUMBER_TEXT_DIGITS_MAX, 0, 0, 0)) != 0;
    ok = (ok & func_020a8bb8(text, &integer_text)) != 0;
    ok = (ok & func_020a89f8(text, data_020d2080)) != 0;
    ok = (ok & func_020a89dc(text, &fraction_text)) != 0;
    func_020a8210(&unused);
    func_020b5618(&fraction_text);
    func_020b5618(&integer_text);
    return ok;
}
CLEAN_AS(func_020b4508, NumberText_SetFixed)

/* func_020b45d0: `text` set to `value` in at most `digits` digits, padded to `digits` as
 * `format` says (enum NumberTextFormat), in full-width characters unless `half_width`; then,
 * when `unit` is not 0, the unit word NumberText_AppendUnit picks. The result of setting the
 * text, or with a unit whether both worked. */
int NumberText_Format(void *text, int value, int digits, int format, int unit, u8 half_width)
{
    char work[NUMBER_TEXT_WORK_SIZE];
    char wide[NUMBER_TEXT_WIDE_SIZE];
    const char *characters = work;

    MI_CpuFill8(work, 0, sizeof(work));
    NumberText_WriteDigits(work, sizeof(work), value, digits);
    if (format == NUMBER_TEXT_LEFT || format == NUMBER_TEXT_LEFT_COMMAS) {
        NumberText_PadSpacesAfter((unsigned char *) work, sizeof(work), digits);
    }
    if (format == NUMBER_TEXT_RIGHT || format == NUMBER_TEXT_RIGHT_COMMAS) {
        NumberText_PadSpacesBefore((unsigned char *) work, sizeof(work), digits);
    }
    if (format == NUMBER_TEXT_ZEROS || format == NUMBER_TEXT_ZEROS_COMMAS) {
        NumberText_PadZeros(work, sizeof(work), digits);
    }
    if (format == NUMBER_TEXT_COMMAS || format == NUMBER_TEXT_LEFT_COMMAS || format == NUMBER_TEXT_RIGHT_COMMAS ||
        format == NUMBER_TEXT_ZEROS_COMMAS) {
        NumberText_InsertCommas(work, sizeof(work), NUMBER_TEXT_COMMA_GROUP);
    }
    NumberText_Reverse((signed char *) work, sizeof(work));
    if (half_width == 0) {
        MI_CpuFill8(wide, 0, sizeof(wide));
        NumberText_ToFullWidth(wide, sizeof(wide), work, sizeof(work));
        characters = wide;
    }
    int ok = func_020a8be4(text, characters);
    if (unit != 0) {
        ok = (ok & NumberText_AppendUnit(text, value, unit)) != 0;
    }
    return ok;
}
CLEAN_AS(func_020b45d0, NumberText_Format)

/* `table[index]`, where a negative index reads the bytes before the table as the ROM does. */
static u8 number_text_table_byte(const u8 *table, int index)
{
    return *(const u8 *) ((uintptr_t) table + (uintptr_t) (intptr_t) index);
}

/* func_020b46a4: the unit word `unit` (1 to 10) for `value` appended to `text`: a message of
 * "st_unit", fixed for most units and chosen by the value's last digit for units 3, 6 and 9
 * (message 0 for any other unit). Whether it loaded and was appended. QUIRK: a negative
 * value's last digit is negative and reads the byte that far before the table. */
int NumberText_AppendUnit(void *text, int value, int unit)
{
    NumberTextPart word;
    int last_digit = value % 10;
    u8 message = 0;

    func_020a8228(&word);
    switch (unit) {
        case 1:
            message = 0;
            break;
        case 2:
            message = 1;
            break;
        case 3:
            message = number_text_table_byte(data_020d20ac, last_digit);
            break;
        case 4:
            message = 5;
            break;
        case 5:
            message = 6;
            break;
        case 6:
            message = number_text_table_byte(data_020d2094, last_digit);
            break;
        case 7:
            message = 10;
            break;
        case 8:
            message = 11;
            break;
        case 9:
            message = number_text_table_byte(data_020d20a0, last_digit);
            break;
        case 10:
            message = 14;
            break;
        default:
            break;
    }
    int ok = func_020b4a20(&word, &message, data_020e5300);
    if (ok != 0) {
        ok = (ok & func_020a89dc(text, &word)) != 0;
    }
    func_020a8210(&word);
    return ok;
}
CLEAN_AS(func_020b46a4, NumberText_AppendUnit)

/* func_020b4758: the reversed work text `src` (little-endian characters) copied to `dst` with
 * each digit, space and comma made full-width, up to its 0x0000 character, which is copied
 * too. QUIRK: only the low byte of each character is looked at. REQUIRES: every character is
 * a digit, a space or a comma, as NumberText_Format's always are; for any other the ROM reads
 * its replacement from address 0, and here the character is copied as it is. Neither size is
 * looked at. */
void NumberText_ToFullWidth(char *dst, unsigned int dst_size, const char *src, unsigned int src_size)
{
    (void) dst_size;
    (void) src_size;
    unsigned int i = 0;
    while (src[i] != 0 || src[i + 1] != 0) {
        int character = (s8) src[i];
        const char *wide = NULL;
        if (character >= '0' && character <= '9') {
            wide = &data_020d20b8[(character - '0') * 2];
        } else if (character == ' ') {
            wide = data_020d2078;
        } else if (character == ',') {
            wide = data_020d207c;
        }
        if (wide != NULL) {
            dst[i + 1] = wide[0];
            dst[i] = wide[1];
        } else {
            dst[i + 1] = 0;
            dst[i] = (char) character;
        }
        i += 2;
    }
    dst[i] = 0;
    dst[i + 1] = 0;
}
CLEAN_AS(func_020b4758, NumberText_ToFullWidth)

/* func_020b47d0: the bytes of the work text before its 0x0000 character reversed, which turns
 * its high-byte-first characters, least significant digit first, into a little-endian text
 * with the most significant digit first. */
void NumberText_Reverse(signed char *work, unsigned int size)
{
    int length = func_020b4950_unk(work, size);
    unsigned int half = (unsigned int) length >> 1;
    int j = length - 1;

    for (unsigned int i = 0; i < half; i++, j--) {
        signed char byte = work[i];
        work[i] = work[j];
        work[j] = byte;
    }
}
CLEAN_AS(func_020b47d0, NumberText_Reverse)

/* func_020b47fc: a comma put in after every `group` digits of the work text (the characters
 * after it moved up by one). It walks the even bytes up to the first 0, counting digits.
 * QUIRK: the work text's characters are high byte first, so its even bytes are the high
 * bytes, all 0: the walk stops at once and no comma is ever written. */
void NumberText_InsertCommas(char *work, unsigned int size, int group)
{
    int count = 0;

    for (int i = 0; (s8) work[i] != 0; i += 2) {
        if ((s8) work[i] < '0' || (s8) work[i] > '9') {
            continue;
        }
        count++;
        if (count < group) {
            continue;
        }
        count = 0;
        unsigned int next = (unsigned int) i + 2;
        if (next < size && (s8) work[next] >= '0' && (s8) work[next] <= '9') {
            NumberText_MoveUp((signed char *) work, (int) size, i, 2);
            work[next] = ',';
            work[next + 1] = 0;
        }
    }
}
CLEAN_AS(func_020b47fc, NumberText_InsertCommas)

/* func_020b4864: the work text filled with '0' characters up to `digits` characters. */
void NumberText_PadZeros(char *work, int size, int digits)
{
    for (int i = func_020b4950_unk(work, (unsigned int) size); i < digits * 2; i += 2) {
        work[i] = 0;
        work[i + 1] = '0';
    }
}
CLEAN_AS(func_020b4864, NumberText_PadZeros)

/* func_020b488c: the work text filled with spaces up to `digits` characters; after the
 * reversal they stand before the number. */
void NumberText_PadSpacesBefore(unsigned char *work, int size, int digits)
{
    for (int i = func_020b4950_unk(work, (unsigned int) size); i < digits * 2; i += 2) {
        work[i] = 0;
        work[i + 1] = ' ';
    }
}
CLEAN_AS(func_020b488c, NumberText_PadSpacesBefore)

/* func_020b48b4: the work text's characters moved up and spaces put in front of them, up to
 * `digits` characters; after the reversal the spaces stand after the number. QUIRK: with
 * more characters than `digits` (a value of 0 with `digits` 0) the distance is negative and
 * NumberText_MoveUp moves the bytes down, two of them before the buffer. */
void NumberText_PadSpacesAfter(unsigned char *work, u32 size, int digits)
{
    int distance = digits * 2 - func_020b4950_unk(work, (unsigned int) size);

    NumberText_MoveUp((signed char *) work, (int) size, 0, distance);
    for (int i = distance - 1; i >= 0; i -= 2) {
        work[i] = ' ';
        work[i - 1] = 0;
    }
}
CLEAN_AS(func_020b48b4, NumberText_PadSpacesAfter)

/* func_020b48ec: `value`'s decimal digits written into the work text, least significant
 * first, each as the low byte of a high-byte-first character, at most `digits` of them; "0"
 * for 0. The high bytes are left as they are (cleared by the caller). QUIRK: a negative value
 * gives characters below '0'. The size is not looked at. */
void NumberText_WriteDigits(char *work, int size, int value, int digits)
{
    (void) size;
    if (value == 0) {
        work[0] = 0;
        work[1] = '0';
        return;
    }
    for (int i = 1; i < digits * 2 && value != 0; i += 2) {
        int rest = value / 10;
        work[i] = (char) ('0' + (value - rest * 10));
        value = rest;
    }
}
CLEAN_AS(func_020b48ec, NumberText_WriteDigits)

/* func_020b4930: the bytes from `start` to `end` - `distance` - 1 moved up by `distance`
 * (last first), nothing when `distance` is 0. */
void NumberText_MoveUp(signed char *bytes, int end, int start, int distance)
{
    if (distance == 0) {
        return;
    }
    for (int i = end - distance - 1; i >= start; i--) {
        bytes[i + distance] = bytes[i];
    }
}
CLEAN_AS(func_020b4930, NumberText_MoveUp)

/* func_020b4954: from byte `at` of the work text on, the offset of the first 0x0000 character
 * (by steps of two), or the first offset at or past `size`; `at` itself is always looked at.
 * The game enters it only through func_020b4950_unk, which starts at 0. */
int NumberText_LengthFrom(char *work, unsigned int size, int unused, unsigned int at)
{
    (void) unused;
    do {
        if (work[at] == 0 && work[at + 1] == 0) {
            break;
        }
        at += 2;
    } while (at < size);
    return (int) at;
}
CLEAN_AS(func_020b4954, NumberText_LengthFrom)
