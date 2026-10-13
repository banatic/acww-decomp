/* func_ov004_022196e8 @ 0x022196e8, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_02252248;
extern int data_ov004_022522f4;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_022196e8;

void *func_ov004_022196e8(UnkStruct_022196e8 *obj)
{
    obj->unk_00 = &data_ov004_02252248;
    obj->unk_EC = &data_ov004_022522f4;
    func_ov004_02210cf0(obj);
    return obj;
}
