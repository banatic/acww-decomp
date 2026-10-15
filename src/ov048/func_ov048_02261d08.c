/* func_ov048_02261d08 @ 0x02261d08, 0xd4 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02261d08 {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0x7cc];
    u8 unk_810;
    u8 pad_811[2];
    u8 unk_813;
};

extern void func_0206844c(void *a, char *b, void *c);
extern int func_ov048_0226254c(struct UnkStruct_02261d08 *self);
extern int func_020984e8(void);
extern int func_02099664(int);
extern void *func_02077bcc(void *record);
extern void func_020a0194(void);
extern int func_020a0174(void);
extern int func_020eb6ac(u32 p);
extern int func_020eb064(u32 p);
extern const u8 data_ov048_02263964[];
extern void *data_ov048_02263d20;

void func_ov048_02261d08(struct UnkStruct_02261d08 *self)
{
    char buf[5];
    u32 p;

    if (self->unk_813 != 0 && func_ov048_0226254c(self) == 0) {
        if (self->unk_813 == 2) {
            buf[0] = 'o';
            func_0206844c(self->unk_40, buf, data_ov048_02263d20);
        } else {
            buf[1] = 'p';
            func_0206844c(self->unk_40, buf + 1, data_ov048_02263d20);
        }
        return;
    }

    p = (u32) func_02077bcc((void *) func_02099664((int) func_020984e8()));
    func_020a0194();
    if (func_020eb6ac(p) != 0) {
        if (func_020eb064(p) != 0) {
            buf[2] = data_ov048_02263964[self->unk_813];
            func_0206844c(self->unk_40, buf + 2, data_ov048_02263d20);
        } else {
            self->unk_810 = 1;
            buf[3] = 'r';
            func_0206844c(self->unk_40, buf + 3, data_ov048_02263d20);
        }
    } else {
        buf[4] = 'q';
        func_0206844c(self->unk_40, buf + 4, data_ov048_02263d20);
    }
    func_020a0174();
}
