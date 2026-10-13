/* func_ov048_02261e78 @ 0x02261e78, 0x58 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_ov048_02263d20;
extern void func_0206844c(void *dst, const char *fmt, void *arg);

struct UnkStruct_02261e78 {
    u8 pad_00[0x40];
    void *p;
    u8 pad_44[0xae - 0x44];
    char c;
    u8 pad_AF[0x813 - 0xaf];
    u8 state;
};

void func_ov048_02261e78(struct UnkStruct_02261e78 *self, int flag)
{
    unsigned char ch;
    char c;

    if (flag != 0) {
        return;
    }
    ch = 0xff;

    switch (self->state) {
        case 2:
            self->c = '[';
            ch = 'j';
            break;
        case 1:
            self->c = '>';
            ch = 'j';
            break;
        case 0:
            ch = '%';
            // falls through
    }

    if (ch != 0xff) {
        c = (char) ch;
        func_0206844c(self->p, &c, data_ov048_02263d20);
    }
}
