/* func_ov048_022619f0 @ 0x022619f0, 0x24 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206844c(void *a, char *b, int c);
extern int data_ov048_02263d20;

struct UnkStruct_022619f0 {
    char pad_00[0x40];
    void *unk_40;
};

void func_ov048_022619f0(struct UnkStruct_022619f0 *obj, int flag)
{
    if (flag == 0) {
        char c = 0x62;
        func_0206844c(obj->unk_40, &c, data_ov048_02263d20);
    }
}
