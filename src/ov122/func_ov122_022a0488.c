/* func_ov122_022a0488 @ 0x022a0488, 0x34 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(const unsigned char *p);
extern void func_ov002_022096d8(unsigned char *p, int v);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov122_0229f2d0(unsigned char *p);

void func_ov122_022a0488(unsigned char *p)
{
    if (func_ov002_0220909c(p + 0x42b0) != 0) {
        func_ov002_022096d8(p + 0x42b0, 0);
        func_ov002_02208098((void *) (p), 0x18);
        func_ov122_0229f2d0(p);
    }
}
