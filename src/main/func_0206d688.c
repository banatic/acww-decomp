/* func_0206d688 @ 0x0206d688, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9a90(void *obj, int arg);
extern int data_020def64;

struct UnkStruct_0206d688 {
    void *unk_00;
};

struct UnkStruct_0206d688 *func_0206d688(struct UnkStruct_0206d688 *obj)
{
    func_020a9a90(obj, 1);
    obj->unk_00 = &data_020def64;
    return obj;
}
