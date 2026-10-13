/* func_ov078_02278b00 @ 0x02278b00, 0xe0 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02278b00 {
    u8 pad_00[0x1e];
    u8 cmd; // 0x1e
    u8 pad_1F[0x40 - 0x1f];
    void *unk_40; // 0x40
    u8 pad_44[0xb4 - 0x44];
    s32 unk_B4; // 0xb4
    u16 unk_B8; // 0xb8
    u16 unk_BA; // 0xba
};

extern int func_020160b4(struct UnkStruct_02278b00 *self);
extern int func_020ab504(int arg);
extern int func_02099fe8(void);
extern void func_0209a050(void);
extern void func_0209a000(void *ptr, int val);
extern void func_020154b4(struct UnkStruct_02278b00 *self, u16 *ptr, int a, int b, int c);
extern void func_02015330(struct UnkStruct_02278b00 *self, u16 *ptr, int a, int b, int c);
extern void func_0206844c(void *dst, void *src, void *data);
extern char data_ov078_02279bd8[];

void func_ov078_02278b00(struct UnkStruct_02278b00 *self)
{
    int res;
    int code;
    char *data;
    struct {
        u8 byte0;
        u8 pad;
        u16 a;
        u16 b;
    } loc;

    res = func_020ab504(func_020160b4(self));

    loc.a = 0xfff1;
    data = data_ov078_02279bd8;
    code = 0;

    switch (self->cmd) {
        case 2:
        case 4:
            if (res == 0) {
                if (func_02099fe8() < 0) {
                    code = 0x1d;
                } else {
                    code = 5;
                }
            }
            break;

        case 13:
        case 19:
            if (res == 0) {
                loc.a = self->unk_B8;
            } else {
                loc.a = self->unk_BA;
            }
            func_020154b4(self, &loc.a, 0, 5, 0);
            func_0209a000(&loc.a, 0);
            code = 0xe;
            break;

        case 20:
            if (res == 0) {
                if (self->unk_B4 >= 0) {
                    func_0209a050();
                    loc.b = 0x13ac;
                    func_02015330(self, &loc.b, 0, 5, 0);
                }
                code = 0x16;
            }
            break;

        default:
            break;
    }

    if (code != 0) {
        loc.byte0 = (u8) code;
        func_0206844c((void *) self->unk_40, &loc, data);
    }
}
