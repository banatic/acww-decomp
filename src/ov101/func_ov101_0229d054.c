/* func_ov101_0229d054 @ 0x0229d054, 0x34 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char);
extern void func_0208e5cc(void *);

void func_ov101_0229d054(unsigned char *param)
{
    if (func_ov002_0220b8ac(param + 0x26f4, 0) != 0) {
        func_ov002_02208098(param, *(param + 0xb6));
        func_0208e5cc(param + 0x229c);
    }
}
