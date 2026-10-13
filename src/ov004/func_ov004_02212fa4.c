/* func_ov004_02212fa4 @ 0x02212fa4, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_0225130c;
extern int data_ov004_022513b8;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02212fa4;

void *func_ov004_02212fa4(UnkStruct_02212fa4 *obj)
{
    obj->unk_00 = &data_ov004_0225130c;
    obj->unk_EC = &data_ov004_022513b8;
    func_ov004_02210cf0(obj);
    return obj;
}
