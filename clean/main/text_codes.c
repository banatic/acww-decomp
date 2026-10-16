/* Small pieces of the game's text (text_codes.h). */
#include "text_codes.h"

#include "clean.h"

static_assert(sizeof(TextParticle) == 8, "TextParticle size");

extern TextParticle data_020cba34[]; /* after a vowel */
extern TextParticle data_020cb9bc[]; /* after a final consonant */

/* One-character texts ("X" and a 0, padded to a word). */
extern const char data_020cb8f0[]; /* ")" */
extern const char data_020cb90c[]; /* "(" */
extern const char data_020cb914[]; /* "$" */
extern const char data_020cb908[]; /* "#" */
extern const char data_020cb900[]; /* "&" */
extern const char data_020cb904[]; /* "/" */
extern const char data_020cb910[]; /* "*" */
extern const char data_020cb8fc[]; /* "%" */
extern const char data_020cb8f8[]; /* "{" */

/* func_02050be0: the value paired with `key` in a table of pairs that ends with key 0, whose
 * first key the caller passes as `first_key`; `key` itself when no pair has it. */
unsigned short TextCodes_Translate(unsigned short key, unsigned short first_key, const TextCodePair *pairs)
{
    u16 current = first_key;
    for (;;) {
        if (key == current) {
            return pairs->value;
        }
        pairs++;
        current = pairs->key;
        if (current == 0) {
            return key;
        }
    }
}
CLEAN_AS(func_02050be0, TextCodes_Translate)

/* func_02050bf8: a particle's form after a vowel (also, for "ro", after a final rieul). */
TextParticle *TextCodes_ParticleAfterVowel(int index)
{
    return &data_020cba34[index];
}
CLEAN_AS(func_02050bf8, TextCodes_ParticleAfterVowel)

/* func_02050c04: a particle's form after a final consonant. */
TextParticle *TextCodes_ParticleAfterConsonant(int index)
{
    return &data_020cb9bc[index];
}
CLEAN_AS(func_02050c04, TextCodes_ParticleAfterConsonant)

/* The codes' texts, by address. */
static int text_address(const char *text)
{
    return (int) (uintptr_t) text;
}

/* func_02050c10: ")". */
int TextCodes_RightParen(void)
{
    return text_address(data_020cb8f0);
}
CLEAN_AS(func_02050c10, TextCodes_RightParen)

/* func_02050c18: "(". */
int TextCodes_LeftParen(void)
{
    return text_address(data_020cb90c);
}
CLEAN_AS(func_02050c18, TextCodes_LeftParen)

/* func_02050c20: "$", which ends a label's text (func_020a8a70). */
int TextCodes_EndCode(void)
{
    return text_address(data_020cb914);
}
CLEAN_AS(func_02050c20, TextCodes_EndCode)

/* func_02050c28: "#", which stands for a newline in a label's text (func_020a8a70). */
int TextCodes_NewlineCode(void)
{
    return text_address(data_020cb908);
}
CLEAN_AS(func_02050c28, TextCodes_NewlineCode)

/* func_02050c30: "&". */
int TextCodes_Ampersand(void)
{
    return text_address(data_020cb900);
}
CLEAN_AS(func_02050c30, TextCodes_Ampersand)

/* func_02050c38: "/". */
int TextCodes_Slash(void)
{
    return text_address(data_020cb904);
}
CLEAN_AS(func_02050c38, TextCodes_Slash)

/* func_02050c40: "*". */
int TextCodes_Asterisk(void)
{
    return text_address(data_020cb910);
}
CLEAN_AS(func_02050c40, TextCodes_Asterisk)

/* func_02050c48: "%". */
int TextCodes_Percent(void)
{
    return text_address(data_020cb8fc);
}
CLEAN_AS(func_02050c48, TextCodes_Percent)

/* func_02050c50: "{". */
int TextCodes_LeftBrace(void)
{
    return text_address(data_020cb8f8);
}
CLEAN_AS(func_02050c50, TextCodes_LeftBrace)

/* func_02050c58: a 16-bit character from two bytes, little-endian; the bytes it took (2). */
unsigned short TextCodes_DecodeChar(u16 *out, const u8 *bytes)
{
    *out = (u16) (bytes[0] | bytes[1] << 8);
    return 2;
}
CLEAN_AS(func_02050c58, TextCodes_DecodeChar)

/* func_02050c78: a 16-bit character (the low half of `c`) as two bytes, little-endian; the
 * bytes it wrote (2). */
int TextCodes_EncodeChar(unsigned char *bytes, int c)
{
    bytes[0] = (u8) c;
    bytes[1] = (u8) (c >> 8);
    return 2;
}
CLEAN_AS(func_02050c78, TextCodes_EncodeChar)
