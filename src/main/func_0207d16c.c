/* func_0207d16c @ 0x0207d16c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern void *func_0207f270(void *);

void func_0207d16c(void *arg0)
{
    void *pvVar1;

    if (func_02003704((void *) func_0208150c((unsigned int) arg0)) != 0) {
        pvVar1 = func_0207f270(arg0);
        *(unsigned char *) ((int) pvVar1 + 0x1e) = 0;
    }
    return;
}
