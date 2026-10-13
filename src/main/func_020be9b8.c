/* func_020be9b8 @ 0x020be9b8, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020beb98(void *p, int value);
extern void func_020be758(void *p);

struct UnkStruct_020be9b8 {
    int unk_00;
    int unk_04;
    int unk_08;
};

void func_020be9b8(struct UnkStruct_020be9b8 *obj)
{
    obj->unk_08--;
    if (obj->unk_08 > 0) {
        return;
    }
    func_020beb98(obj, obj->unk_04);
    func_020be758(obj);
}
