/* Runtime-only helpers for the opt-in Spanish resource adaptation. */
#ifndef CLEAN_MAIN_LOCALIZED_GRAMMAR_H
#define CLEAN_MAIN_LOCALIZED_GRAMMAR_H

#include "../../runtime/localized_grammar.h"
#include "message_reader.h"
#include "message_texts.h"
#include "player_id.h"
#include "player_record.h"
#include "player_records.h"

static inline int localized_grammar_player_gender(void)
{
    u8 *record = PlayerRecords_Current();
    return record != NULL ? PlayerId_Gender((const s8 *) PlayerRecord_Player(record)) != 0 : -1;
}

/* The reader's existing persistent small texts are unused by the Korean article code.
 * Spanish articles fit their ten-byte buffers with a closing UTF-16 zero. */
static inline const char *localized_grammar_article(const void *text, unsigned state)
{
    if (!localized_grammar_enabled()) {
        return NULL;
    }
    const u8 *attributes = (const u8 *) text + 8;
    int index = localized_grammar_article_index(attributes, 10, state);
    if (index < 0) {
        return NULL;
    }
    u8 article = (u8) index;
    extern MessageReader data_021f4dac;
    MessageText10 *cached = (MessageText10 *) (void *) data_021f4dac.items[article];
    if (cached->end == 0) {
        if (MessageReader_LoadMessage(cached, &article, "st_article") == 0) {
            return NULL;
        }
        cached->end = 1;
    }
    return cached->text;
}

#endif
