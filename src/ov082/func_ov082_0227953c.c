/* func_ov082_0227953c @ 0x0227953c, 0x30 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov082_02279018(void *, void *);

int func_ov082_0227953c(char *a)
{
    if (func_0202edc8(a) == 0) {
        return 0;
    }
    func_0201c280(a, a + 0x658);
    func_ov082_02279018(a + 0x658, a);
    return 1;
}
