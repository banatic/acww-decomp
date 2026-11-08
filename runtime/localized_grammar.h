/* Opt-in Spanish text rules for the localized Clean build, not the original ROM contract. */
#ifndef RUNTIME_LOCALIZED_GRAMMAR_H
#define RUNTIME_LOCALIZED_GRAMMAR_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static inline int localized_grammar_enabled(void)
{
    const char *language = getenv("ACWW_GRAMMAR");
    return language != NULL && strcmp(language, "es") == 0;
}

static inline int localized_grammar_article_index(const uint8_t *attributes, uint32_t size, unsigned state)
{
    if (size < 10 || state > 1) {
        return -1;
    }
    unsigned article = attributes[state == 0 ? 8 : 9];
    return article < 6 ? (int) article : -1;
}

/* Alternatives are UTF-16LE zero-terminated strings inside the tag, not unbounded C strings. */
static inline const uint8_t *localized_grammar_form(const uint8_t *bytes, uint32_t size, int gender)
{
    if (gender < 0 || gender > 2) {
        return NULL;
    }
    uint32_t at = 0;
    for (int form = 0; form <= gender; form++) {
        uint32_t start = at;
        while (at + 1 < size && (bytes[at] != 0 || bytes[at + 1] != 0)) {
            at += 2;
        }
        if (at + 1 >= size) {
            return NULL;
        }
        if (form == gender) {
            return at == start ? NULL : bytes + start;
        }
        at += 2;
    }
    return NULL;
}

/* Western byte-font character codes used by the donor's case-conversion table. */
static inline int localized_grammar_upper(int character)
{
    if ((character >= 'a' && character <= 'z') || (character >= 0xe0 && character <= 0xfe && character != 0xf7)) {
        return character - 0x20;
    }
    switch (character) {
        case 0x9a:
            return 0x8a;
        case 0x9c:
            return 0x8c;
        case 0x9e:
            return 0x8e;
        case 0xff:
            return 0x9f;
        default:
            return character;
    }
}

#endif
