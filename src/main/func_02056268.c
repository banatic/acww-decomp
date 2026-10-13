/* func_02056268 @ 0x02056268, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
} UnkStruct_02056268;

extern int func_020e9948(int a, int b);
extern void MI_CpuCopy8(UnkStruct_02056268 *a, int b, int c);

int func_02056268(UnkStruct_02056268 *p, int key)
{
    int ret;
    ret = func_020e9948(key, p->unk_00);
    if (ret == 0) {
        return 0;
    }
    MI_CpuCopy8(p, ret, p->unk_00);
    return ret;
}
