/* func_ov049_02261080 @ 0x02261080, 0x44 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc6c(void);
extern void func_0206844c(int a, char *b, int c);
extern int data_ov049_02263298;

struct UnkStruct_02261080 {
    char pad_00[0x40];
    int unk_40;
};

void func_ov049_02261080(struct UnkStruct_02261080 *param)
{
    char local[8];
    if (func_0206fc6c()) {
        local[0] = 16;
        func_0206844c(param->unk_40, &local[0], data_ov049_02263298);
    } else {
        local[1] = 15;
        func_0206844c(param->unk_40, &local[1], data_ov049_02263298);
    }
}
