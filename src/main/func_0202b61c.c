/* func_0202b61c @ 0x0202b61c, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02099fe8(void);
extern void func_0207de14(void *dst, void *src);
extern void func_0202d694(void *p);
extern unsigned int func_0208150c(void *p);
extern u32 func_020036e8(unsigned char *);
extern int func_0202da38(void *a, void *b, void *c, int n, int base, int offset, int scale, int multiplier, int selected);

extern struct {
    u32 w;
    u8 b;
} data_020c89e8;

struct UnkStruct_0202b61c {
    u8 pad_00[0x100];
    void *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122[0x7a];
    u16 unk_19C;
    u8 unk_19E;
};

struct UnkStruct_0202b61c_2 {
    u8 pad_00[0x830];
    void *unk_830;
};

int func_0202b61c(struct UnkStruct_0202b61c *self)
{
    u16 temp[2];
    void *field;

    if (func_02099fe8() != -1) {
        field = ((struct UnkStruct_0202b61c_2 *) self->unk_100)->unk_830;

        func_0207de14(temp, field);
        self->unk_19C = temp[0];

        if (self->unk_19C != 0xfff1) {
            self->unk_19E = 1;
        } else {
            func_0202d694(&temp[1]);
            self->unk_19C = temp[1];
            self->unk_19E = 0;
        }

        func_0202da38(self, self->unk_104, self->unk_122, 0x1e, func_020036e8((unsigned char *) func_0208150c(field)),
                      data_020c89e8.w, data_020c89e8.b, 0, 0);
        return 1;
    }
    return 0;
}
