/* func_ov048_02262390 @ 0x02262390, 0x26 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_02068364(void *p, int v);
extern void func_02068440(void *p);

void func_ov048_02262390(void *self, int flag)
{
    void *p = *(void **) ((char *) self + 0x40);
    if (flag) {
        func_02068364(p, 1);
    } else {
        func_02068364(p, 0);
    }
    func_02068440(p);
}
