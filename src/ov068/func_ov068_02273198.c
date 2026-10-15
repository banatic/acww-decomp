/* func_ov068_02273198 @ 0x02273198, 0x1c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_022732bc(void *p, int x);

struct __unknown_02273198 {
    unsigned char pad_00[0x59a];
    unsigned short unk_59A;
};

int func_ov068_02273198(struct __unknown_02273198 *p)
{
    p->unk_59A = 31;
    func_ov068_022732bc(p, 0);
    return 1;
}
