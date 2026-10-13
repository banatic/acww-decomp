/* func_0207d91c @ 0x0207d91c, 0x5a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0207f1c8(void);
extern unsigned int func_0209b5ec(void);
extern void func_0208150c(unsigned int a);
extern int func_02003704(void);
extern int func_0209c370(unsigned int a);
extern unsigned int func_0209bfe8(unsigned int a);
extern int func_0209dffc(void);
extern int func_0209e3ac(unsigned int a, unsigned int b, int size);
extern void MI_CpuCopy8(unsigned int a, unsigned int b, int size);

void func_0207d91c(unsigned int a, unsigned int b)
{
    unsigned int r4;

    func_0207f1c8();
    r4 = func_0209b5ec();
    func_0208150c(a);
    if (func_02003704() == 0) {
        return;
    }
    if (func_0209c370(r4) == 0) {
        return;
    }
    r4 = func_0209bfe8(r4);
    if (func_0209dffc() != 0 || func_0209e3ac(b, r4, 0x3f) == -1) {
        MI_CpuCopy8(b, r4, 8);
    }
}
