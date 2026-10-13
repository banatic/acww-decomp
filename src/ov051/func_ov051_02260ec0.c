/* func_ov051_02260ec0 @ 0x02260ec0, 0x44 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc58(void *param);
extern void func_0206844c(int a, char *b, int c);
extern int data_ov051_022615c0;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02260ec0;

void func_ov051_02260ec0(UnkStruct_02260ec0 *param0)
{
    char local[8];

    if (func_0206fc58(param0) != 0) {
        local[0] = 0x29;
        func_0206844c(param0->unk_40, local, data_ov051_022615c0);
    } else {
        local[1] = 9;
        func_0206844c(param0->unk_40, &local[1], data_ov051_022615c0);
    }
}
