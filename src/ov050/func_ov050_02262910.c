/* func_ov050_02262910 @ 0x02262910, 0x60 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a000(void *ptr, int val);
extern void func_020154b4(void *self, void *ptr, int a, int b, int c);

typedef struct {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0xb4 - 0x1f];
    unsigned char *unk_B4;
    char pad_B8[0xd0 - 0xb8];
    unsigned int unk_D0;
} SelfType;

void func_ov050_02262910(SelfType *self)
{
    int sp_arg;
    unsigned short local[2];

    local[0] = 0x1020;
    if (func_0209a000(&local[0], 0)) {
        local[1] = 0x1020;
        sp_arg = 0;
        func_020154b4(self, &local[1], 0, 5, sp_arg);
    }
    if (self->unk_1E == 0x1f) {
        self->unk_D0 = 0x20;
        self->unk_B4[0x73e] = 2;
    } else {
        self->unk_D0 = 0x26;
    }
}
