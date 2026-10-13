/* func_ov051_02260d94 @ 0x02260d94, 0x2c bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    unsigned int unk_40;
} UnkStruct_02260d94;

extern int func_020a1298(UnkStruct_02260d94 *p);
extern void func_0206844c(unsigned int a, char *b, unsigned int c);
extern unsigned int data_ov051_022615c0;

void func_ov051_02260d94(UnkStruct_02260d94 *param)
{
    if (func_020a1298(param)) {
        char local = 0x30;
        func_0206844c(param->unk_40, &local, data_ov051_022615c0);
    }
}
