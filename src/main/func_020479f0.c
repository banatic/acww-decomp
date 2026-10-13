/* func_020479f0 @ 0x020479f0, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02047a28(int, int, int, int);
extern void func_02046680(void);

void func_020479f0(int a, int b, int c)
{
    int i, j;
    int k = 0;

    for (j = 0; j < 2; j++) {
        for (i = k; i < c; i++) {
            func_02047a28(a, b, i, j);
        }
    }
    func_02046680();
}
