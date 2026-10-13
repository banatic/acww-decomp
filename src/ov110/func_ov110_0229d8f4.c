/* func_ov110_0229d8f4 @ 0x0229d8f4, 0x34 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *p, int b);
extern int func_ov002_02208098(void *p, unsigned char c);
extern void func_0208e5cc(void *p);

void func_ov110_0229d8f4(void *p)
{
    if (func_ov002_0220b8ac((char *) p + 0x2738, 1)) {
        func_ov002_02208098(p, *(unsigned char *) ((char *) p + 0xf8));
        func_0208e5cc((char *) p + 0x22e0);
    }
}
