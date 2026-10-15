/* func_0207e054 @ 0x0207e054, 0x6e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_020807a8(int, int);
extern int func_02081d20(int);
extern int func_0207f270(int);
extern int func_020794c4(unsigned char *);
extern int func_0207e0c4(int, int, int);
extern void func_02081a80(int, int);

int func_0207e054(int arg1, int arg2, int arg3)
{
    int result = 0x58;

    if (func_02003704((void *) func_0208150c(arg1)) != 0) {
        if (arg3 == 0) {
            arg3 = func_020984e8();
        }
        if (arg3 != 0 && arg2 == 0) {
            arg2 = func_020807a8(arg1, func_02099870(arg3));
        }
        if (arg2 != 0) {
            result = func_02081d20(arg2);
            result = func_0207e0c4(arg3, result, func_020794c4((unsigned char *) func_0207f270(arg1)));
            func_02081a80(arg2, result);
        }
    }
    return result;
}
