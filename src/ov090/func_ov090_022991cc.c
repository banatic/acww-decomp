/* func_ov090_022991cc @ 0x022991cc, 0x14 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022080a0(void *obj, int a2, int a3);

struct UnkStruct_022991cc {
    char pad_00[0x94];
    unsigned char flag;
};

void func_ov090_022991cc(struct UnkStruct_022991cc *obj)
{
    obj->flag = 1;
    func_ov002_022080a0(obj, 2, 1);
}
