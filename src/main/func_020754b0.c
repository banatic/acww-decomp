/* func_020754b0 @ 0x020754b0, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020b65c4(void);
extern unsigned int func_020a132c(void);
extern int func_020a1250(int);
extern void func_020a1254(void *, unsigned char);
extern void MI_CpuCopy8(const void *, void *, unsigned int);

void func_020754b0(unsigned char *payload, unsigned int length, int player)
{
    int v;
    void *p;

    v = func_020b65c4();
    if (v != 12) {
        return;
    }

    p = (void *) func_020a132c();
    if (p == 0) {
        return;
    }

    MI_CpuCopy8(payload, (void *) func_020a1250((int) func_020a132c()), 8);
    func_020a1254((void *) func_020a132c(), 1);
}
