/* func_ov107_0229d5e0 @ 0x0229d5e0, 0x34 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *ptr, int val);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0208e5cc(void *ptr);

void func_ov107_0229d5e0(void *self)
{
    if (func_ov002_0220b8ac((char *) self + 0x270c, 0) != 0) {
        func_ov002_02208098((void *) (self), ((unsigned char *) self)[0xbb]);
        func_0208e5cc((char *) self + 0x22b4);
    }
}
