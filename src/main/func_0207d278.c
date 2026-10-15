/* func_0207d278 @ 0x0207d278, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern void *func_0207f270(int);
extern int func_020794c4(void *);

int func_0207d278(int arg0)
{
    void *p;
    if (func_02003704((void *) func_0208150c(arg0)) != 0 && (p = func_0207f270(arg0)) != 0 &&
        (func_020794c4(p) == 0 || func_020794c4(p) == 1)) {
        return 1;
    }
    return 0;
}
