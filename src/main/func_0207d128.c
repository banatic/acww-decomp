/* func_0207d128 @ 0x0207d128, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern int func_0207f270(int);
extern void func_02079468(unsigned char *);

void func_0207d128(int arg0)
{
    int val;

    val = func_02003704((void *) func_0208150c(arg0));
    if (val != 0) {
        func_02079468((unsigned char *) func_0207f270(arg0));
    }
    return;
}
