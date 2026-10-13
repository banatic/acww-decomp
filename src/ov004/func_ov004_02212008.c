/* func_ov004_02212008 @ 0x02212008, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_02252a7c;
extern int data_ov004_02252b28;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02212008;

void *func_ov004_02212008(UnkStruct_02212008 *obj)
{
    obj->unk_00 = &data_ov004_02252a7c;
    obj->unk_EC = &data_ov004_02252b28;
    func_ov004_02210cf0(obj);
    return obj;
}
