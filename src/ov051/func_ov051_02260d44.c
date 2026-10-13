/* func_ov051_02260d44 @ 0x02260d44, 0x50 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a12d4(void);
extern char func_ov051_022605e8(void *param, int arg);
extern void func_0206844c(unsigned int a, char *b, unsigned int c);
extern unsigned int data_ov051_022615c0;

struct UnkStruct_02260d44 {
    char pad_00[0x40];
    unsigned int unk_40;
};

void func_ov051_02260d44(struct UnkStruct_02260d44 *param)
{
    char buf[2];
    if (func_020a12d4()) {
        buf[0] = func_ov051_022605e8(param, 21);
        func_0206844c(param->unk_40, &buf[0], data_ov051_022615c0);
    } else {
        buf[1] = func_ov051_022605e8(param, 31);
        func_0206844c(param->unk_40, &buf[1], data_ov051_022615c0);
    }
}
