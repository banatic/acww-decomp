/* func_ov104_0229cb78 @ 0x0229cb78, 0x70 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229cb78 UnkStruct_0229cb78;
struct UnkStruct_0229cb78 {
    char pad_00[0xa8];
    int a8;
    int ac;
    char pad_B0[9];
    unsigned char c;
};

extern void func_ov104_0229d4a8(UnkStruct_0229cb78 *, unsigned char);
extern int func_ov104_0229d8a8(UnkStruct_0229cb78 *, unsigned char);
extern int func_ov104_0229d858(UnkStruct_0229cb78 *, unsigned char);
extern int func_0206fe54(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov094_0229b1d8(void *);

void func_ov104_0229cb78(UnkStruct_0229cb78 *self)
{
    unsigned char c;

    c = self->c;
    func_ov104_0229d4a8(self, c);
    self->a8 = func_ov104_0229d8a8(self, c);
    self->ac = func_ov104_0229d858(self, c);

    if (func_0206fe54()) {
        self->a8 -= 2;
        self->ac -= 2;
    }

    func_ov002_02208098((void *) (self), 0x1c);
    func_ov094_0229b1d8((char *) self + 0xd58);
}
