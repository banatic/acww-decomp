/* func_ov004_02213914 @ 0x02213914, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02210cf0(void *);
extern int data_ov004_02251c6c;
extern int data_ov004_02251d18;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02213914;

void *func_ov004_02213914(UnkStruct_02213914 *obj)
{
    obj->unk_00 = &data_ov004_02251c6c;
    obj->unk_EC = &data_ov004_02251d18;
    func_ov004_02210cf0(obj);
    return obj;
}
