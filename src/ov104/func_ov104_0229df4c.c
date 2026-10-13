/* func_ov104_0229df4c @ 0x0229df4c, 0x38 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229d484(int, unsigned char);
extern void func_ov104_0229dd00(int);
extern void func_ov104_0229d500(int);
extern void func_ov094_022999d8(void);
extern int func_ov002_02209d8c(int);

void func_ov104_0229df4c(int r0)
{
    if (func_ov002_02209d8c(r0 + 0x2488)) {
        func_ov104_0229d484(r0, *(unsigned char *) (r0 + 0xb7));
        func_ov104_0229dd00(r0);
        func_ov094_022999d8();
    } else {
        func_ov104_0229d500(r0);
    }
}
