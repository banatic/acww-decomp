/* func_02056928 @ 0x02056928, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020dd184;
extern int data_020dd164;
extern void func_020568dc(void *self);

struct UnkStruct_02056928 {
    void *unk_00;
    int pad_04;
    int unk_08;
    int unk_0C;
    int unk_10;
};

struct UnkStruct_02056928 *func_02056928(struct UnkStruct_02056928 *obj)
{
    obj->unk_00 = &data_020dd184;
    obj->unk_08 = 0;
    obj->unk_0C = 0;
    obj->unk_10 = 0x1000;
    obj->unk_00 = &data_020dd164;
    func_020568dc(obj);
    return obj;
}
