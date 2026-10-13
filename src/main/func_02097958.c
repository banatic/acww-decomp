/* func_02097958 @ 0x02097958, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021dc7bc;
extern void *func_02065f70(void);
extern void func_0209529c(char *buf);
extern void func_02095208(char *buf, void *p);
extern int func_0209871c(char *global, char *buf);
extern int func_020988d8(void);
extern void func_0209526c(char *buf);

int func_02097958(void)
{
    char buf[0x20];
    void *p;
    int result;

    p = func_02065f70();
    if (p == 0) {
        return -1;
    }

    func_0209529c(buf);
    func_02095208(buf, p);
    result = func_0209871c(&data_021dc7bc, buf);
    if (func_020988d8() != 0) {
        func_0209526c(buf);
        return result;
    } else {
        func_0209526c(buf);
        return -2;
    }
}
