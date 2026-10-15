/* func_ov054_02262620 @ 0x02262620, 0xc0 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8e];
    short unk_8E;
    unsigned char pad_90[0x4e8 - 0x90];
    int unk_4E8;
    unsigned char pad_4EC[0x804 - 0x4ec];
    short unk_804;
    unsigned char pad_806[0x808 - 0x806];
    int unk_808;
} UnkStruct_02262620;

extern int func_0202ec58(void *arg0);
extern void *func_020984e8(void);
extern int func_ov054_02260474(void *self);
extern int func_020a7278(void);
extern void func_ov054_02262528(UnkStruct_02262620 *self, int mode);
extern int func_020a12e8(void);
extern int func_02099020(void *p, int k);
extern void func_020356c4(int a, int b, int c, int d);

int func_ov054_02262620(UnkStruct_02262620 *self)
{
    void *p;

    if (!func_0202ec58((void *) self)) {
        return 0;
    }

    p = func_020984e8();

    if (func_ov054_02260474(self)) {
        if (func_020a7278()) {
            func_ov054_02262528(self, 2);
        } else {
            func_ov054_02262528(self, 9);
        }
    } else {
        if (func_020a12e8() != 0 && func_02099020(p, 9) == 0) {
            func_ov054_02262528(self, 0);
        } else {
            func_ov054_02262528(self, 2);
        }
    }

    self->unk_804 = self->unk_8E;
    self->unk_4E8 |= 2;

    if (self->unk_808 == 0) {
        func_020356c4(0x11, 0x55, 0x7f, 0);
    } else if (self->unk_808 == 1) {
        if (func_ov054_02260474(self) == 0) {
            func_020356c4(0x11, 0x56, 0x7f, 0);
        }
    }

    return 1;
}
