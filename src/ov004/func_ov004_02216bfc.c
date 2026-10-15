/* func_ov004_02216bfc @ 0x02216bfc, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02210cf0(void *);
extern int data_ov004_02251d98;
extern int data_ov004_02251e44;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02216bfc;

void *func_ov004_02216bfc(UnkStruct_02216bfc *obj)
{
    obj->unk_00 = &data_ov004_02251d98;
    obj->unk_EC = &data_ov004_02251e44;
    func_ov004_02210cf0(obj);
    return obj;
}
