/* func_ov051_02260cd8 @ 0x02260cd8, 0x44 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02260cd8;

extern int func_020a12c0(void);
extern void func_0206844c(int a, char *b, int c);
extern int data_ov051_022615c0;

void func_ov051_02260cd8(UnkStruct_02260cd8 *self)
{
    char buf[8];
    if (func_020a12c0()) {
        buf[0] = 0x19;
        func_0206844c(self->unk_40, buf, data_ov051_022615c0);
    } else {
        buf[1] = 0xf;
        func_0206844c(self->unk_40, buf + 1, data_ov051_022615c0);
    }
}
