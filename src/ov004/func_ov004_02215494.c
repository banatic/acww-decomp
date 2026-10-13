/* func_ov004_02215494 @ 0x02215494, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_02252ba8;
extern int data_ov004_02252c54;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02215494;

void *func_ov004_02215494(UnkStruct_02215494 *obj)
{
    obj->unk_00 = &data_ov004_02252ba8;
    obj->unk_EC = &data_ov004_02252c54;
    func_ov004_02210cf0(obj);
    return obj;
}
