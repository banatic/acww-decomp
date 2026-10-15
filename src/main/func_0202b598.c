/* func_0202b598 @ 0x0202b598, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0202b598 UnkStruct_0202b598;
struct UnkStruct_0202b598 {
    u8 pad_00[0x100];
    void *unk_100;
    u8 pad_104[0x19c - 0x104];
    u16 unk_19C;
    u8 unk_19E;
};

extern int func_02099fe8(void);
extern void func_0202d694(u16 *p);
extern unsigned int func_0208150c(u32 val);
extern u32 func_020036e8(unsigned char *);
extern struct {
    u32 a;
    u8 b;
} data_020c8ca8;
extern int func_0202da38(UnkStruct_0202b598 *self, char *p1, char *p2, int count, int base, int offset, int scale, int a4,
                         int a5);

int func_0202b598(UnkStruct_0202b598 *self)
{
    u16 local;
    u16 val;

    if (func_02099fe8() == -1) {
        goto fail;
    }

    func_0202d694(&local);
    val = local;
    self->unk_19C = val;
    self->unk_19E = 0;

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e,
                  func_020036e8((unsigned char *) func_0208150c(*(u32 *) ((char *) self->unk_100 + 0x830))), data_020c8ca8.a,
                  data_020c8ca8.b, 0, 0);

    return 1;

fail:
    return 0;
}
