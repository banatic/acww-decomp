/* func_ov074_02279878 @ 0x02279878, 0x30 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov074_02278fa8(void *, void *);

int func_ov074_02279878(char *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, p + 0x658);
    func_ov074_02278fa8(p + 0x658, p);
    return 1;
}
