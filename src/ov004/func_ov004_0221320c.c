/* func_ov004_0221320c @ 0x0221320c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_02251564;
extern int data_ov004_02251610;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221320c;

void *func_ov004_0221320c(UnkStruct_0221320c *obj)
{
    obj->unk_00 = &data_ov004_02251564;
    obj->unk_EC = &data_ov004_02251610;
    func_ov004_02210cf0(obj);
    return obj;
}
