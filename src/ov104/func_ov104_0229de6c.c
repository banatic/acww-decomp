/* func_ov104_0229de6c @ 0x0229de6c, 0x34 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *ptr, int flag);
extern void func_ov002_02208098(void *ptr, unsigned char byte);
extern void func_0208e5cc(void *ptr);

void func_ov104_0229de6c(void *p)
{
    if (func_ov002_0220b8ac((char *) p + 0x28f8, 0) != 0) {
        func_ov002_02208098(p, *(unsigned char *) ((char *) p + 0xbb));
        func_0208e5cc((char *) p + 0x24a0);
    }
}
