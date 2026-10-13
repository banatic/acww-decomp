/* func_ov004_02213694 @ 0x02213694, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_02251b40;
extern int data_ov004_02251bec;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02213694;

void *func_ov004_02213694(UnkStruct_02213694 *obj)
{
    obj->unk_00 = &data_ov004_02251b40;
    obj->unk_EC = &data_ov004_02251bec;
    func_ov004_02210cf0(obj);
    return obj;
}
