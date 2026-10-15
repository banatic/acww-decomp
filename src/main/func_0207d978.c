/* func_0207d978 @ 0x0207d978, 0x5a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207f1c8(unsigned int);
extern int func_0209b5ec(void *);
extern int func_0208150c(unsigned int);
extern int func_02003704(int);
extern int func_0209c370(int);
extern int func_0209bfec(int);
extern int func_0209dffc(int);
extern int func_0209e3ac(unsigned int, int, unsigned int);
extern void MI_CpuCopy8(unsigned int, int, unsigned int);

void func_0207d978(unsigned int param0, unsigned int param1)
{
    int v;
    v = (func_0209b5ec((void *) func_0207f1c8(param0)));
    if (func_02003704(func_0208150c(param0)) == 0) {
        return;
    }
    if (func_0209c370(v) == 0) {
        return;
    }
    v = func_0209bfec(v);
    if (func_0209dffc(v) == 0 && func_0209e3ac(param1, v, 0x3f) != -1) {
        return;
    }
    MI_CpuCopy8(param1, v, 8);
}
