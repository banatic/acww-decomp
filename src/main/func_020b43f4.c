/* func_020b43f4 @ 0x020b43f4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b547c(void *);
extern void func_020a9b04(void *);
extern void MI_CpuFill8(void *, int, int);

void func_020b43f4(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_020b547c((char *) r4 + 0x4c);
    func_020a9b04((char *) r4 + 0xaf0);
    MI_CpuFill8((char *) r4 + 0xafc, 0, 0xa00);
}
