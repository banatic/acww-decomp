/* func_020a8e4c @ 0x020a8e4c, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps both result words loaded before the first compare; the plain condition compares a before loading b */

extern void func_020a8754(int *p);
extern void func_020a8764(int *p, int param);
extern void func_020a8308(int *p);
extern int func_02068bc8(void);
struct UnkStruct_020a8e4c {
    char pad_00[0x38];
    unsigned char unk_38;
    char pad_39[0x7c - 0x39];
    int unk_7C;
};
void func_020a8e4c(struct UnkStruct_020a8e4c *self, int param2)
{
    int local[5];
    int a;
    int b;
    if (self->unk_7C == 1) {
        func_020a8754(local);
        func_020a8764(local, param2);
        a = local[0];
        if ((param2 && param2) && param2) {
        }
        b = local[1];
        if ((a == 0xff) && (b == 0)) {
            func_020a8308(local);
            self->unk_38 = func_02068bc8();
        }
    }
}
