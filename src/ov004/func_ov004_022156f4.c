/* func_ov004_022156f4 @ 0x022156f4, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02210cf0(void *);
extern int data_ov004_02250c04;
extern int data_ov004_02250cb0;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_022156f4;

void *func_ov004_022156f4(UnkStruct_022156f4 *obj)
{
    obj->unk_00 = &data_ov004_02250c04;
    obj->unk_EC = &data_ov004_02250cb0;
    func_ov004_02210cf0(obj);
    return obj;
}
