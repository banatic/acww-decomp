/* func_0207d91c @ 0x0207d91c, 0x5a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0207f1c8(unsigned int);
extern unsigned int func_0209b5ec(void *);
extern unsigned int func_0208150c(unsigned int a);
extern int func_02003704(void *);
extern int func_0209c370(unsigned int a);
extern unsigned int func_0209bfe8(unsigned int a);
extern int func_0209dffc(const unsigned char *);
extern int func_0209e3ac(unsigned int a, unsigned int b, int size);
extern void MI_CpuCopy8(unsigned int a, unsigned int b, int size);

void func_0207d91c(unsigned int a, unsigned int b)
{
    unsigned int r4;

    r4 = func_0209b5ec((void *) func_0207f1c8(a));
    if (func_02003704((void *) func_0208150c(a)) == 0) {
        return;
    }
    if (func_0209c370(r4) == 0) {
        return;
    }
    r4 = func_0209bfe8(r4);
    if (func_0209dffc((const unsigned char *) r4) != 0 || func_0209e3ac(b, r4, 0x3f) == -1) {
        MI_CpuCopy8(b, r4, 8);
    }
}
