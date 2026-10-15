/* func_ov122_022a1864 @ 0x022a1864, 0x34 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206e2d0(void *);
extern void func_ov095_0229bf7c(void *, int);
extern void func_ov002_022091cc(void *);
extern void func_ov122_022a1850(void);

void func_ov122_022a1864(void *param)
{
    func_0206e2d0((char *) param + 0x3ce8);
    func_ov095_0229bf7c((char *) param + 0xc0, 6);
    func_ov002_022091cc((char *) param + 0x42b0);
    // clang-format off
    asm {
        mov r0, param
    }
    // clang-format on
    func_ov122_022a1850();
}
