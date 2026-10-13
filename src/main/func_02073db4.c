/* func_02073db4 @ 0x02073db4, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073de0(int a, int b, int c);

void func_02073db4(int a)
{
    int i;
    int j = 0;
    int k = 3;

    for (i = 3; i >= 0; i--) {
        func_02073de0(a, i, j);
    }
}
