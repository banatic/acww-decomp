/* func_ov119_0229bdf0 @ 0x0229bdf0, 0x5e bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov119_0229ad5c(void *self);
extern int func_020ee45c(void *self);
extern void func_ov090_02298fa4(int x);
extern int func_ov119_0229ae68(void *self);
extern int func_020eae80(int x);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_ov119_0229a410(void *self, int x);
extern void func_ov119_0229a714(void *self);
extern void func_ov119_0229bbe4(void *self);

typedef struct {
    unsigned char pad_00[0xb1];
    unsigned char unk_B1;
    unsigned char pad_B2[2];
    unsigned char unk_B4;
} SelfType;

void func_ov119_0229bdf0(SelfType *self)
{
    if (self->unk_B1 != 0) {
        self->unk_B1 = 0;
        func_ov119_0229ad5c(self);
        (void) func_ov090_02298fa4(func_020ee45c(self));
        if (func_ov119_0229ae68(self) != 0) {
            if (func_020eae80(self->unk_B4) == 0) {
                func_ov002_02208098(self, 0x11);
            }
        }
    } else {
        func_ov119_0229a410(self, 2);
        func_ov119_0229a714(self);
        func_ov119_0229bbe4(self);
    }
}
