/* func_ov080_02279030 @ 0x02279030, 0x30 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov080_02278dec(void *a, void *b);

int func_ov080_02279030(void *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, (char *) p + 0x658);
    func_ov080_02278dec((char *) p + 0x658, p);
    return 1;
}
