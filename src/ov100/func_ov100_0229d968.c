/* func_ov100_0229d968 @ 0x0229d968, 0x38 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *p, int arg);
extern void func_ov002_02208098(void *p, unsigned char arg);
extern void func_0208e5cc(void *p);

void func_ov100_0229d968(void *self)
{
    if (func_ov002_0220b8ac((char *) self + 0x26cc, 0) != 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x2924));
        func_0208e5cc((char *) self + 0x2274);
    }
}
