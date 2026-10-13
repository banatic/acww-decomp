/* func_0202fc5c @ 0x0202fc5c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eaca0(int *out, int x, int y);
extern void func_020ea8c8(int *out, int x, int *v1, int *v2);
extern void func_020ea838(int x);

void func_0202fc5c(int a, int b, int c, int d)
{
    int buf1[3];
    int buf2[3];
    int buf3[4];

    func_020eaca0(buf1, c, b);
    func_020eaca0(buf2, d, b);
    func_020ea8c8(buf3, a, buf1, buf2);
    func_020ea838(a);
}
