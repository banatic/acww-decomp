/* func_ov068_022730ac @ 0x022730ac, 0x1c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x59a];
    unsigned short unk_59A;
} Something;

extern void func_ov068_022732bc(Something *obj, int a, int b);

int func_ov068_022730ac(Something *obj)
{
    obj->unk_59A = 0;
    func_ov068_022732bc(obj, 1, 0);
    return 1;
}
