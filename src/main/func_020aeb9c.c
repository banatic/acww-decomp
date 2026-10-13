/* func_020aeb9c @ 0x020aeb9c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aef2c(int *a, int *b);
extern void func_020b00fc(int *p1, int *p2, int p3, int p4, int p5, int p6, int p7);

void func_020aeb9c(int *a, int *b)
{
    int v1, v2, v3;
    v1 = func_020aef2c(a, b);
    v2 = 0x25;
    v3 = 0;
    func_020b00fc(a + 1, b, 0x151f, 1, v1, v2, v3);
}
