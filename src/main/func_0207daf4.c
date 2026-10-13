/* func_0207daf4 @ 0x0207daf4, 0x52 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_02003704(int);
extern int func_02080814(int);
extern int func_0207f1c8(int);
extern int func_0209b5ec(int);
extern int func_0209beb0(int, int, int);

void func_0207daf4(int arg0, int arg1)
{
    int tmp;

    if (func_02003704(func_0208150c(arg0)) && func_02003704(func_0208150c(arg1)) && (tmp = func_02080814(arg0))) {
        func_0209beb0(func_0209b5ec(func_0207f1c8(arg0)), func_0209b5ec(func_0207f1c8(arg1)), tmp);
    }
}
