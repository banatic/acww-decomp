/* func_020ab960 @ 0x020ab960, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e3fcc;
extern void *func_020a9a90(void *obj, int param);

typedef struct {
    int *unk_00;
    char pad_04[0xA0];
    int unk_A4;
    int unk_A8;
} UnkStruct_020ab960;

UnkStruct_020ab960 *func_020ab960(UnkStruct_020ab960 *obj)
{
    func_020a9a90(obj, 1);
    obj->unk_00 = &data_020e3fcc;
    obj->unk_A4 = 0;
    obj->unk_A8 = 0;
    return obj;
}
