/* func_0207d128 @ 0x0207d128, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void);
extern int func_02003704(void);
extern void func_0207f270(int);
extern void func_02079468(void);

void func_0207d128(int arg0)
{
    int val;

    func_0208150c();
    val = func_02003704();
    if (val != 0) {
        func_0207f270(arg0);
        func_02079468();
    }
    return;
}
