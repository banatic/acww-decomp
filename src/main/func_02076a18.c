/* func_02076a18 @ 0x02076a18, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int data_021e5a2c;
extern char data_021dc7aa[];

extern void func_020736bc(int, int *, int);
extern void func_020789f4(int *, int *, int *);
extern int func_0207cec0(int *, int);
extern int func_020807c0(int, int);
extern int func_020984fc(int);
extern int func_02099870(int);
extern int func_02081e94(int, int, char *, int);

void func_02076a18(int a, int b, int c, int d)
{
    int s0;
    int s1;
    int s2;
    int x;
    int r5;

    func_020736bc(data_020ccf94, &s0, a);
    func_020789f4(&s1, &s2, &s0);
    x = func_0207cec0(&data_021e5a2c, s1);
    if (x != 0) {
        r5 = func_020807c0(x, s2);
        if (r5 != 0) {
            int ret;
            ret = func_02099870((int) func_020984fc(d));
            func_02081e94(r5, ret, data_021dc7aa, 0);
        }
    }
}
