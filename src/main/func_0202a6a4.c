/* func_0202a6a4 @ 0x0202a6a4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0200368c(void *, int, void *, int);
extern void *data_020c8b20;

struct B_0202a6a4 {
    u8 pad_00[0x830];
    u32 unk_830;
};

struct A_0202a6a4 {
    u8 pad_00[0x100];
    struct B_0202a6a4 *b;
    u8 buffer[0x1e];
    u8 unk_122;
};

struct Out_0202a6a4 {
    void *ptr;
    u8 byte;
};

void func_0202a6a4(struct A_0202a6a4 *a, struct Out_0202a6a4 *out)
{
    func_0200368c(a->buffer, 0x1e, data_020c8b20, func_020036e8(func_0208150c(a->b->unk_830)));
    a->unk_122 = 5;
    out->ptr = a->buffer;
    out->byte = a->unk_122;
}
