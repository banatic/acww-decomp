/* func_ov003_0221ba10 @ 0x0221ba10, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226539c(void *);
extern int data_ov003_02238434;
extern int data_ov003_022384f8;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221ba10;

void *func_ov003_0221ba10(UnkStruct_0221ba10 *obj)
{
    obj->unk_00 = &data_ov003_02238434;
    obj->unk_EC = &data_ov003_022384f8;
    func_ov009_0226539c(obj);
    return obj;
}
