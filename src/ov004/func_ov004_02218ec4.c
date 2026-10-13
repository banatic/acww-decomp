/* func_ov004_02218ec4 @ 0x02218ec4, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_022510b4;
extern int data_ov004_02251160;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02218ec4;

void *func_ov004_02218ec4(UnkStruct_02218ec4 *obj)
{
    obj->unk_00 = &data_ov004_022510b4;
    obj->unk_EC = &data_ov004_02251160;
    func_ov004_02210cf0(obj);
    return obj;
}
