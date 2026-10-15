/* func_ov004_0220c250 @ 0x0220c250, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Work {
    u8 pad_00[0x12c];
    u32 unk_12C;
};

typedef struct {
    u32 data[16];
} BUFFER;

extern u32 func_020984e8(void);
extern unsigned int func_020996a0(unsigned int);
extern u16 *func_020adf50(void *record);
extern void *func_020b5630(BUFFER *);
extern int func_020b45d0(BUFFER *, u16, int, int, int, int);
extern void func_02068404(u32, int, BUFFER *);
extern u16 func_020adda8(u16 *);
extern u8 func_020adde4(u16);
extern int func_020683e4(u32, int, void *, u32);
extern void *func_020b5618(BUFFER *);
extern u32 data_ov004_0224fbe4;

void func_ov004_0220c250(struct Work *self)
{
    u8 bytes[2];
    BUFFER buf;
    u16 *p;

    if (self->unk_12C == 0) {
        return;
    }

    p = func_020adf50((void *) func_020996a0((unsigned int) func_020984e8()));

    func_020b5630(&buf);

    func_020b45d0(&buf, *(u16 *) p, 10, 0, 0, 0);
    func_02068404(self->unk_12C, 0, &buf);
    func_020b45d0(&buf, func_020adda8(p), 10, 0, 0, 0);
    func_02068404(self->unk_12C, 1, &buf);

    if (func_020adde4(*(u16 *) p) != 0) {
        bytes[0] = (u8) (func_020adde4(*(u16 *) p) - 1);
        func_020683e4(self->unk_12C, 2, &bytes[0], data_ov004_0224fbe4);
    }
    bytes[1] = func_020adde4(*(u16 *) p);
    func_020683e4(self->unk_12C, 3, &bytes[1], data_ov004_0224fbe4);

    func_020b5618(&buf);
}
