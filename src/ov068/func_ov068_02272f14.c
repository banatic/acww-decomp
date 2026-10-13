/* func_ov068_02272f14 @ 0x02272f14, 0x24 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226539c(void *);
extern int data_ov068_02277750;
extern int data_ov068_02277814;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02272f14;

void *func_ov068_02272f14(UnkStruct_02272f14 *obj)
{
    obj->unk_00 = &data_ov068_02277750;
    obj->unk_EC = &data_ov068_02277814;
    func_ov009_0226539c(obj);
    return obj;
}
