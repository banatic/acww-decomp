/* func_02089c88 @ 0x02089c88, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208a088(void *obj);
extern char data_020e2008;

struct UnkStruct_02089c88 {
    void *unk_00;
    char pad_04[0x3C];
    int unk_40;
};

struct UnkStruct_02089c88 *func_02089c88(struct UnkStruct_02089c88 *obj)
{
    func_0208a088(obj);
    obj->unk_00 = &data_020e2008;
    obj->unk_40 = 0;
    return obj;
}
