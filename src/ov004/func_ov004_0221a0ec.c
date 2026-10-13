/* func_ov004_0221a0ec @ 0x0221a0ec, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_02252e00;
extern int data_ov004_02252eac;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221a0ec;

void *func_ov004_0221a0ec(UnkStruct_0221a0ec *obj)
{
    obj->unk_00 = &data_ov004_02252e00;
    obj->unk_EC = &data_ov004_02252eac;
    func_ov004_02210cf0(obj);
    return obj;
}
