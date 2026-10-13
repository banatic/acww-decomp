/* func_02076c3c @ 0x02076c3c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_020736bc(int, char *, int);
extern void func_02096440(char *, char *, char *);
extern int func_020984fc(int);
extern void func_02099808(int, unsigned char);
extern void func_020997e0(int, unsigned char);

void func_02076c3c(int p1, int p2, int p3, int p4)
{
    char buf[3];
    int x;
    func_020736bc(data_020ccf94, buf, p1);
    func_02096440(buf, buf + 1, buf + 2);
    x = func_020984fc(p4);
    func_02099808(x, buf[1]);
    func_020997e0(x, buf[2]);
}
