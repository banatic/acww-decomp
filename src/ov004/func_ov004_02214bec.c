/* func_ov004_02214bec @ 0x02214bec, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02210cf0(void *);
extern int data_ov004_02252824;
extern int data_ov004_022528d0;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02214bec;

void *func_ov004_02214bec(UnkStruct_02214bec *obj)
{
    obj->unk_00 = &data_ov004_02252824;
    obj->unk_EC = &data_ov004_022528d0;
    func_ov004_02210cf0(obj);
    return obj;
}
