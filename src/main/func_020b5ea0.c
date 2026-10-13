/* func_020b5ea0 @ 0x020b5ea0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b64c0(int);
extern void func_020b64f0(int, int, int, int, int, int, int);
extern int data_021f69b8;

int func_020b5ea0(int p0, int p1, int p2, int p3, short p4, int p5, int p6)
{
    if (func_020b64c0(p1)) {
        func_020b64f0((int) &data_021f69b8, p1, p2, p3, (int) p4, p5, p6);
        return 1;
    } else {
        return 0;
    }
}
