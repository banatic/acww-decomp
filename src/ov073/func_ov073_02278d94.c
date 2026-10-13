/* func_ov073_02278d94 @ 0x02278d94, 0xb0 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099fe8(void *);
extern void func_02099f1c(void *, void (*)(void));
extern void func_0209a000(unsigned short *, int);
extern void func_ov073_02278e44(void);

typedef struct {
    unsigned char pad_00[0xc4];
    int unk_C4;
} St;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char b[4];
} UnkStruct_02278d94;

int func_ov073_02278d94(St *self)
{
    int count = 0;
    int i;
    int r7 = func_02099fe8(self);
    int r6;
    UnkStruct_02278d94 local;

    for (i = 0; i < 10; i++) {
        if (self->unk_C4 >= 10) {
            self->unk_C4 -= 10;
            count++;
        }
    }

    r6 = count;
    if (self->unk_C4 != 0) {
        r6 = count + 1;
    }

    func_02099f1c(local.b, func_ov073_02278e44);

    if (r7 < 0 || local.b[2] < r6) {
        return 0;
    }

    while (count > 0) {
        local.unk_00 = 0x153a;
        func_0209a000(&local.unk_00, 0);
        count--;
    }

    if (self->unk_C4 > 0) {
        self->unk_C4--;
        local.unk_02 = self->unk_C4 + 0x1531;
        func_0209a000(&local.unk_02, 0);
    }

    return 1;
}
