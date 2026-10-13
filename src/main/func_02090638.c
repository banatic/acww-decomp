/* func_02090638 @ 0x02090638, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205556c(int *a, int b, int c);
extern int data_020e2498[];

struct UnkStruct_02090638 {
    char pad_00[0x24];
    int unk_24;
};

int func_02090638(struct UnkStruct_02090638 *obj, int idx)
{
    int flag = 1;
    if (func_0205556c(&obj->unk_24, idx + 0x6d656666, data_020e2498[idx]) == 0) {
        flag = 0;
    }
    return flag;
}
