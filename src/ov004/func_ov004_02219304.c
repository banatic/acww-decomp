/* func_ov004_02219304 @ 0x02219304, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_022518e8;
extern int data_ov004_02251994;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02219304;

void *func_ov004_02219304(UnkStruct_02219304 *obj)
{
    obj->unk_00 = &data_ov004_022518e8;
    obj->unk_EC = &data_ov004_02251994;
    func_ov004_02210cf0(obj);
    return obj;
}
