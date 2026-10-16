/* The message file the talks' answers are read from, and the 72-character text class an
 * answer's text is.
 *
 * - The answers' message file (class data_020e3fcc, 0xac bytes; one global object,
 *   data_021f4670, built at start-up with entries of 0x0c bytes): a message file of bmg_file.h
 *   that reads a message into a buffer it is handed rather than one of its own. Its vtable has
 *   the destructor, the deleting destructor, the buffer's address (slot 2) and its size
 *   (slot 3). SelectBmg_LoadText opens /script/<language>/<name>.bmg, reads one message into a
 *   text's characters and copies the message's INF1 entry (its attributes) into a record.
 * - The 72-character text (vtable data_020e3f9c, 0x5c bytes), derived from the label base of
 *   text_label.h (built by func_020a8cac, destroyed by func_020a8c38, emptied by
 *   func_020a8c1c), whose characters start at 0x12. Its vtable has the destructor, the deleting
 *   destructor, the capacity in characters and the characters' address. The talks' answers
 *   (talk_answers.h) hold one each; other parts of main use the class too. */
#ifndef CLEAN_MAIN_SELECT_BMG_H
#define CLEAN_MAIN_SELECT_BMG_H

#include "block_020a8248.h"
#include "bmg_file.h"
#include "text_label.h" /* TextVtable */
#include "types.h"

#define SELECT_BMG_TEXT_START 0x12
#define SELECT_BMG_TEXT_CAPACITY 72

typedef struct SelectBmg {
    BmgFile file; /* 0x00: vtable data_020e3fcc */
    u8 *buffer;   /* 0xa4: where the next message is read, or NULL */
    u32 size;     /* 0xa8: its size in bytes */
} SelectBmg;

typedef struct SelectBmgText {
    const TextVtable *vtable;              /* 0x00: data_020e3f9c */
    u8 base_04[SELECT_BMG_TEXT_START - 4]; /* 0x04: the label base's */
    char chars[SELECT_BMG_TEXT_CAPACITY];  /* 0x12 */
    u8 pad_5a[2];
} SelectBmgText;

int SelectBmg_LoadText(SelectBmgText *text, const char *path, const u8 *index, Block020a8248 *record);
char *SelectBmgText_Chars(SelectBmgText *text);
int SelectBmgText_Capacity(void);
SelectBmgText *SelectBmgText_Delete(SelectBmgText *text);
SelectBmgText *SelectBmgText_Destruct(SelectBmgText *text);
SelectBmgText *SelectBmgText_Construct(SelectBmgText *text);
u32 SelectBmg_Size(SelectBmg *file);
u8 *SelectBmg_Buffer(SelectBmg *file);
void SelectBmg_ClearBuffer(SelectBmg *file);
void SelectBmg_SetBuffer(SelectBmg *file, u8 *buffer, u32 size);
SelectBmg *SelectBmg_Delete(SelectBmg *file);
SelectBmg *SelectBmg_Destruct(SelectBmg *file);
SelectBmg *SelectBmg_Construct(SelectBmg *file);

#endif
