/* func_ov003_0220f5f8 @ 0x0220f5f8, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_02008258(void *self, unsigned int val);
extern int func_02008dc0(void *self, short a, int b, int c);
extern int func_0200d4e8(void *self, int a, int b, int c);

typedef struct {
    char pad_00[0x8e];
    short short_8e;
    char pad_90[0x2d0 - 0x90];
    char sub_2d0[0x7e0 - 0x2d0];
    unsigned char unk_7E0;
    char pad_7E1[0x0f];
    unsigned int unk_7F0;
    char pad_7F4[8];
    unsigned int unk_7FC;
} Objs;

void func_ov003_0220f5f8(Objs *self)
{
    unsigned char flag = self->unk_7E0;
    if (func_02056f94(&self->sub_2d0)) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        if (flag) {
            func_02008dc0(self, self->short_8e, 6, -1);
        } else {
            func_0200d4e8(self, 3, 1, -1);
        }
    }
}
