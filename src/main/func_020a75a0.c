/* func_020a75a0 @ 0x020a75a0, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b65c4(void);
extern void func_02084f8c(void);
extern void MI_CpuCopy8(void *param1, void *param2, int param3);

void func_020a75a0(void *param0)
{
    unsigned char local;
    void *sp;

    local = 0;
    func_020b65c4();
    MI_CpuCopy8(param0, &local, 1);
    if (local != 0) {
        func_02084f8c();
    }
}
