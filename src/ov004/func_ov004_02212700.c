/* func_ov004_02212700 @ 0x02212700, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02210cf0(void *);
extern int data_ov004_02250d30;
extern int data_ov004_02250ddc;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02212700;

void *func_ov004_02212700(UnkStruct_02212700 *obj)
{
    obj->unk_00 = &data_ov004_02250d30;
    obj->unk_EC = &data_ov004_02250ddc;
    func_ov004_02210cf0(obj);
    return obj;
}
