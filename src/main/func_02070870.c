/* func_02070870 @ 0x02070870, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020707d0(char *);
extern void func_020a8874(char *, int, int);
extern void func_020a8a70(int, char *, int, unsigned char);
extern void func_020707b8(char *);

void func_02070870(int a, int b, int c, int d, unsigned char e)
{
    char buffer[0x64];
    if (d == 0) {
        e = 0;
    }
    func_020707d0(buffer);
    func_020a8874(buffer, b, c);
    func_020a8a70(a, buffer, d, e);
    func_020707b8(buffer);
}
