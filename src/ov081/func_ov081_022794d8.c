/* func_ov081_022794d8 @ 0x022794d8, 0x30 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov081_02278fd8(void *, void *);

int func_ov081_022794d8(char *a)
{
    if (func_0202edc8(a) == 0) {
        return 0;
    }
    func_0201c280(a, a + 0x658);
    func_ov081_02278fd8(a + 0x658, a);
    return 1;
}
