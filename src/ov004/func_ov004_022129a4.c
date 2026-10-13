/* func_ov004_022129a4 @ 0x022129a4, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_022511e0;
extern int data_ov004_0225128c;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_022129a4;

void *func_ov004_022129a4(UnkStruct_022129a4 *obj)
{
    obj->unk_00 = &data_ov004_022511e0;
    obj->unk_EC = &data_ov004_0225128c;
    func_ov004_02210cf0(obj);
    return obj;
}
