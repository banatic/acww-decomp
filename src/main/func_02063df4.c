/* func_02063df4 @ 0x02063df4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02063ea4(void *param);
extern void func_020e930c(void *ptr, int value);
extern void func_02063db4(void *param);
extern int data_020de64c;

typedef struct {
    void *unk_00;
    int unk_04;
} UnkStruct_02063df4;

UnkStruct_02063df4 *func_02063df4(UnkStruct_02063df4 *param)
{
    func_02063ea4(param);
    param->unk_00 = &data_020de64c;
    func_020e930c(&param->unk_04, 1);
    func_02063db4(param);
    return param;
}
