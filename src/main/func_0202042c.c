/* func_0202042c @ 0x0202042c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[0x1e];
    u8 unk_122;
} UnkStruct_0202042c;

typedef struct {
    char pad_00[0x830];
    void *unk_830;
} InnerA;

typedef struct {
    void *ptr;
    u8 byte;
} UnkStruct_0202042c_2;

typedef struct {
    u32 word;
    u8 byte;
} UnkStruct_0202042c_3;

extern UnkStruct_0202042c_3 data_020c8ab0;
extern void *func_0208150c(void *ptr);
extern void *func_020036e8(void *ptr);
extern void func_0202da38(void *a, void *b, void *c, int d, void *e, u32 f, int g, int h, int i);

void func_0202042c(UnkStruct_0202042c *a, UnkStruct_0202042c_2 *b)
{
    void *tmp;

    tmp = func_020036e8(func_0208150c(((InnerA *) a->unk_100)->unk_830));
    func_0202da38(a, &a->unk_104, &a->unk_122, 0x1e, tmp, data_020c8ab0.word, 1, 0xe, data_020c8ab0.byte);
    b->ptr = &a->unk_104;
    b->byte = a->unk_122;
}
