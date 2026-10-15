/* func_ov004_02214410 @ 0x02214410, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02210cf0(void *);
extern int data_ov004_022524a0;
extern int data_ov004_0225254c;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02214410;

void *func_ov004_02214410(UnkStruct_02214410 *obj)
{
    obj->unk_00 = &data_ov004_022524a0;
    obj->unk_EC = &data_ov004_0225254c;
    func_ov004_02210cf0(obj);
    return obj;
}
