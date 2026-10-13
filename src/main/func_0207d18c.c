/* func_0207d18c @ 0x0207d18c, 0x6a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void func_02099870(int);
extern int func_020951bc(void);
extern int func_02099020(int, int);
extern void func_0208150c(int);
extern int func_02003704(void);
extern unsigned char *func_0207f270(int);
extern int func_0207d278(int);

int func_0207d18c(int a, int b)
{
    int flag2;
    int result;

    if (b == 0) {
        b = func_020984e8();
    }
    result = 0;
    flag2 = result;
    if (b != 0) {
        func_02099870(b);
        if (func_020951bc() != 0) {
            if (func_02099020(b, 1) == 0) {
                func_0208150c(a);
                if (func_02003704() != 0) {
                    if (*(unsigned char *) (func_0207f270(a) + 0x1e) == 0x20) {
                        flag2 = 1;
                    }
                }
            }
        }
    }
    if (flag2 != 0) {
        if (func_0207d278(a) != 0) {
            result = 1;
        }
    }
    return result;
}
