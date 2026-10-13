/* func_02097900 @ 0x02097900, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021e5a2c;
int func_02065f64(void);
void func_02003780(char *p);
void func_020037ac(char *p, int v);
int func_0207cf14(int base, char *p);
int func_0207cf74(void);
void func_02003750(char *p);

int func_02097900(void)
{
    int result;
    int base;
    char local[20];

    base = (int) &data_021e5a2c;
    result = func_02065f64();
    if (result == 0) {
        return -1;
    }

    func_02003780(local);
    func_020037ac(local, result);

    result = func_0207cf14(base, local);
    if (func_0207cf74() != 0) {
        func_02003750(local);
        return result;
    } else {
        func_02003750(local);
        return -2;
    }
}
