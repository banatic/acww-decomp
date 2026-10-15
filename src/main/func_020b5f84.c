/* func_020b5f84 @ 0x020b5f84, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f69a0;
extern int func_020b64c0(int);
extern void func_020b64f0(int *p, int b, int c, int d, int e, int f, int g);

int func_020b5f84(int a, int b, int c, int d, short e, int f, int g)
{
    if (func_020b64c0(b)) {
        func_020b64f0(&data_021f69a0, b, c, d, (int) e, f, g);
        return 1;
    }
    return 0;
}
