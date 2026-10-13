/* func_ov078_02279758 @ 0x02279758, 0x30 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov078_02278f74(void *, void *);

int func_ov078_02279758(void *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, (char *) p + 0x658);
    func_ov078_02278f74((char *) p + 0x658, p);
    return 1;
}
