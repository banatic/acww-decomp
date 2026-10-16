/* Small pieces of the game's text: the one-character codes of its 8-bit label texts, the
 * Korean particles whose form depends on the syllable before them, a table lookup for
 * characters, and reading and writing a 16-bit character as two bytes, little-endian. */
#ifndef CLEAN_MAIN_TEXT_CODES_H
#define CLEAN_MAIN_TEXT_CODES_H

#include "types.h"

/* A particle in its two forms (data_020cb9bc after a final consonant, data_020cba34 after a
 * vowel): up to three 16-bit characters ending with a 0. By index: 0 eun/neun, 1 eul/reul,
 * 2 i/ga, 3 a/ya, 4 i/(none), 5 gwa/wa, 6 euro/ro, 7 ui, 8 igun/gun, 9 ege, 10 do, 11 iraneun/
 * raneun, 12 irago/rago, 13 irani/rani, 14 irang/rang. */
typedef struct TextParticle {
    u16 text[4];
} TextParticle;

/* A pair of TextCodes_Translate's table. */
typedef struct TextCodePair {
    u16 key;
    u16 value;
} TextCodePair;

unsigned short TextCodes_Translate(unsigned short key, unsigned short first_key, const TextCodePair *pairs);
TextParticle *TextCodes_ParticleAfterVowel(int index);
TextParticle *TextCodes_ParticleAfterConsonant(int index);
int TextCodes_RightParen(void);
int TextCodes_LeftParen(void);
int TextCodes_EndCode(void);
int TextCodes_NewlineCode(void);
int TextCodes_Ampersand(void);
int TextCodes_Slash(void);
int TextCodes_Asterisk(void);
int TextCodes_Percent(void);
int TextCodes_LeftBrace(void);
unsigned short TextCodes_DecodeChar(u16 *out, const u8 *bytes);
int TextCodes_EncodeChar(unsigned char *bytes, int c);

#endif
