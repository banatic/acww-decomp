/* func_0207ae74 @ 0x0207ae74, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(unsigned char *);
extern int func_02003704(int);
extern void func_0207d2b4(unsigned char *, void *);

void func_0207ae74(unsigned char *arg0, void *arg1)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(arg0))) {
            func_0207d2b4(arg0, arg1);
        }
        arg0 += 0x7ec;
    }
}
