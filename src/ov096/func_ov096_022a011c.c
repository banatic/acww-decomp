/* func_ov096_022a011c @ 0x022a011c, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *ptr, int val);
extern void func_ov002_02208098(void *ptr, unsigned char byte);
extern void func_0208e5cc(void *ptr);

void func_ov096_022a011c(void *arg0)
{
    if (func_ov002_0220b8ac((char *) arg0 + 0x2958, 1)) {
        func_ov002_02208098(arg0, *((unsigned char *) arg0 + 0xba));
        func_0208e5cc((char *) arg0 + 0x2500);
    }
}
