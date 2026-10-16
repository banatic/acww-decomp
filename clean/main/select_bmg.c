/* The talks' answers' message file and the 72-character text class (select_bmg.h). */
#include "select_bmg.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "text_base.h" /* TextBase_Construct, TextBase_Destruct, TextBase_Clear */

static_assert(offsetof(SelectBmg, buffer) == 0xa4, "select bmg");
static_assert(sizeof(SelectBmg) == 0xac, "select bmg");
static_assert(offsetof(SelectBmgText, chars) == SELECT_BMG_TEXT_START, "select bmg text");
static_assert(sizeof(SelectBmgText) == 0x5c, "select bmg text");

/* The classes' vtables. */
extern const u8 data_020e3fcc[]; /* the message file */
extern const u8 data_020e3f9c[]; /* the 72-character text */

/* The answers' message file (built by __sinit_020c6c54). */
extern SelectBmg data_021f4670;

typedef char *(*SelectBmgTextChars)(SelectBmgText *text);
typedef int (*SelectBmgTextCapacity)(SelectBmgText *text);

/* func_020ab83c: message `*index` of the message file at `path` read into the characters of
 * `text` (at most its capacity in bytes), and the message's INF1 entry copied into `record`.
 * The file is closed again and forgets the text's buffer. Returns whether the message was
 * read (BmgFile_LoadMessage).
 * QUIRK: whether the file opened, and whether the message was read, is not looked at: the
 * message is looked for and the entry (as it is then) copied either way. */
int SelectBmg_LoadText(SelectBmgText *text, const char *path, const u8 *index, Block020a8248 *record)
{
    char *chars = ((SelectBmgTextChars) (uintptr_t) text->vtable->buffer)(text);
    int capacity = ((SelectBmgTextCapacity) (uintptr_t) text->vtable->capacity)(text);
    SelectBmg_SetBuffer(&data_021f4670, (u8 *) chars, (u32) capacity);
    BmgFile_Open(&data_021f4670.file, path);
    int loaded = BmgFile_LoadMessage(&data_021f4670.file, index);
    void *entry = BmgFile_Entry(&data_021f4670.file);
    Block020a8248_Copy(record, entry);
    BmgFile_Close(&data_021f4670.file);
    SelectBmg_ClearBuffer(&data_021f4670);
    return loaded;
}
CLEAN_AS(func_020ab83c, SelectBmg_LoadText)

/* func_020ab89c (the text's slot 3): the address of the characters. */
char *SelectBmgText_Chars(SelectBmgText *text)
{
    return text->chars;
}
CLEAN_AS(func_020ab89c, SelectBmgText_Chars)

/* func_020ab8a0 (slot 2): the capacity. */
int SelectBmgText_Capacity(void)
{
    return SELECT_BMG_TEXT_CAPACITY;
}
CLEAN_AS(func_020ab8a0, SelectBmgText_Capacity)

/* func_020ab8a4 (slot 1): destroyed (SelectBmgText_Destruct) and freed. */
SelectBmgText *SelectBmgText_Delete(SelectBmgText *text)
{
    text->vtable = (const TextVtable *) data_020e3f9c;
    TextBase_Destruct((TextBase *) text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_020ab8a4, SelectBmgText_Delete)

/* func_020ab8c4 (slot 0): the destructor: its vtable, then the label base's destructor. */
SelectBmgText *SelectBmgText_Destruct(SelectBmgText *text)
{
    text->vtable = (const TextVtable *) data_020e3f9c;
    TextBase_Destruct((TextBase *) text);
    return text;
}
CLEAN_AS(func_020ab8c4, SelectBmgText_Destruct)

/* func_020ab8dc: the constructor: the label base's, its vtable, then the text emptied. */
SelectBmgText *SelectBmgText_Construct(SelectBmgText *text)
{
    TextBase_Construct(text);
    text->vtable = (const TextVtable *) data_020e3f9c;
    TextBase_Clear(text);
    return text;
}
CLEAN_AS(func_020ab8dc, SelectBmgText_Construct)

/* func_020ab8fc (the file's slot 3): the size of the buffer. */
u32 SelectBmg_Size(SelectBmg *file)
{
    return file->size;
}
CLEAN_AS(func_020ab8fc, SelectBmg_Size)

/* func_020ab904 (slot 2): the buffer's address. */
u8 *SelectBmg_Buffer(SelectBmg *file)
{
    return file->buffer;
}
CLEAN_AS(func_020ab904, SelectBmg_Buffer)

/* func_020ab90c: no buffer. */
void SelectBmg_ClearBuffer(SelectBmg *file)
{
    file->buffer = NULL;
    file->size = 0;
}
CLEAN_AS(func_020ab90c, SelectBmg_ClearBuffer)

/* func_020ab91c: the next message is read into `buffer`, of `size` bytes. */
void SelectBmg_SetBuffer(SelectBmg *file, u8 *buffer, u32 size)
{
    file->buffer = buffer;
    file->size = size;
}
CLEAN_AS(func_020ab91c, SelectBmg_SetBuffer)

/* func_020ab928 (slot 1): destroyed (SelectBmg_Destruct) and freed. */
SelectBmg *SelectBmg_Delete(SelectBmg *file)
{
    file->file.vtable = data_020e3fcc;
    BmgFile_Destruct(file);
    Heap_OperatorDeleteB(file);
    return file;
}
CLEAN_AS(func_020ab928, SelectBmg_Delete)

/* func_020ab948 (slot 0): the destructor: its vtable, then the file base's destructor (the
 * file closed). */
SelectBmg *SelectBmg_Destruct(SelectBmg *file)
{
    file->file.vtable = data_020e3fcc;
    BmgFile_Destruct(file);
    return file;
}
CLEAN_AS(func_020ab948, SelectBmg_Destruct)

/* func_020ab960: the constructor: a file base whose files have entries of 0x0c bytes, its
 * vtable, no buffer. */
SelectBmg *SelectBmg_Construct(SelectBmg *file)
{
    BmgFile_Construct(&file->file, 1);
    file->file.vtable = data_020e3fcc;
    file->buffer = NULL;
    file->size = 0;
    return file;
}
CLEAN_AS(func_020ab960, SelectBmg_Construct)
