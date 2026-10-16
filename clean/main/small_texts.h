/* Four small text classes on the text base of text_label.h (the same four vtable entries: the
 * destructor, the deleting destructor, the capacity and the address of the characters):
 *
 * - a wide text of 10 16-bit characters (vtable data_020e194c, 0x24 bytes); func_02081bc4
 *   builds one on its stack (villager_memory_entry.c);
 * - a label of 22 8-bit characters (vtable data_020e18d4, 0x28 bytes), built by func_02021c4c
 *   and func_02068644;
 * - a wide text of 4 16-bit characters (vtable data_020e1934, 0x18 bytes), as long as a
 *   villager's catchphrase (villager_catchphrase.h): CatchphraseWide_CopyOut copies its
 *   characters out;
 * - a label of 10 8-bit characters (vtable data_020e1904, 0x1c bytes), into which
 *   NpcLookup_CatchphraseToWide loads a villager's first catchphrase. */
#ifndef CLEAN_MAIN_SMALL_TEXTS_H
#define CLEAN_MAIN_SMALL_TEXTS_H

#include "text_label.h"
#include "types.h"

#define WIDE10_TEXT_CAPACITY 10
#define LABEL22_TEXT_CAPACITY 22
#define CATCHPHRASE_WIDE_CAPACITY 4
#define LABEL10_TEXT_CAPACITY 10

typedef struct Wide10Text {
    const TextVtable *vtable; /* data_020e194c */
    u8 base_04[0xa];          /* the text base's */
    u16 text[WIDE10_TEXT_CAPACITY];
} Wide10Text;

typedef struct Label22Text {
    const TextVtable *vtable; /* data_020e18d4 */
    u8 base_04[0xe];          /* the text base's */
    char text[LABEL22_TEXT_CAPACITY];
} Label22Text;

typedef struct CatchphraseWide {
    const TextVtable *vtable; /* data_020e1934 */
    u8 base_04[0xa];          /* the text base's */
    u16 text[CATCHPHRASE_WIDE_CAPACITY];
} CatchphraseWide;

typedef struct Label10Text {
    const TextVtable *vtable; /* data_020e1904 */
    u8 base_04[0xe];          /* the text base's */
    char text[LABEL10_TEXT_CAPACITY];
} Label10Text;

int Wide10Text_Buffer(int text);
int Wide10Text_Capacity(void);
Wide10Text *Wide10Text_DestructDelete(Wide10Text *text);
Wide10Text *Wide10Text_Destruct(Wide10Text *text);
Wide10Text *Wide10Text_Construct(Wide10Text *text);

int Label22Text_Buffer(int label);
int Label22Text_Capacity(void);
Label22Text *Label22Text_DestructDelete(Label22Text *label);
Label22Text *Label22Text_Destruct(Label22Text *label);
Label22Text *Label22Text_Construct(Label22Text *label);

int CatchphraseWide_Buffer(int text);
void CatchphraseWide_CopyOut(CatchphraseWide *text, u16 *dst, int count);
int CatchphraseWide_Capacity(void);
CatchphraseWide *CatchphraseWide_DestructDelete(CatchphraseWide *text);
CatchphraseWide *CatchphraseWide_Destruct(CatchphraseWide *text);
CatchphraseWide *CatchphraseWide_Construct(CatchphraseWide *text);

int Label10Text_Buffer(int label);
int Label10Text_Capacity(void);
Label10Text *Label10Text_DestructDelete(Label10Text *label);
Label10Text *Label10Text_Destruct(Label10Text *label);
Label10Text *Label10Text_Construct(Label10Text *label);

#endif
