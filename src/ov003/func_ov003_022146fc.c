/* func_ov003_022146fc @ 0x022146fc, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_02008258(void *obj, int value);
extern void func_020109fc(void *obj, int a, int b, int c);
extern void func_0205eae0(void *p, int a, int b, int c);

typedef struct {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x5a0 - 0x2d4];
    int unk_5A0;
    char pad_5A4[0x7f0 - 0x5a4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
} UnkStruct_022146fc;

void func_ov003_022146fc(UnkStruct_022146fc *self)
{
    if (func_02056f94(&self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_020109fc(self, 0x6c, 6, 6);
        func_0205eae0(&self->unk_5A0, 0x13, 6, 0);
    }
}
