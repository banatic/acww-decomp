/* func_ov128_0229bf34 @ 0x0229bf34, 0x4c bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov128_0229bae0(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov127_02299bbc(void *p, unsigned char c);
extern void func_ov127_02299c08(void *p, unsigned char c, int n);
extern void func_ov128_0229bb20(void *self);

typedef struct UnkStruct_0229bf34 {
    char pad_00[0x4a4];
    char sub_4a4;
    char pad_4A5[0x2d6b - 0x4a4 - 1];
    unsigned char unk_2D6B;
} UnkStruct_0229bf34;

void func_ov128_0229bf34(UnkStruct_0229bf34 *self)
{
    int r;

    r = func_ov128_0229bae0();
    if (r != self->unk_2D6B) {
        func_ov002_02208098((void *) (self), 6);
        func_ov127_02299bbc((char *) self + 0x4a4, self->unk_2D6B);
        func_ov128_0229bb20(self);
    } else {
        func_ov127_02299c08((char *) self + 0x4a4, self->unk_2D6B, 1);
        func_ov128_0229bb20(self);
    }
}
