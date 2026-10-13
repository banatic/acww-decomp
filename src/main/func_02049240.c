/* func_02049240 @ 0x02049240, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204930c(int a);

void func_02049240(int a)
{
    int j;
    int i;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            func_0204930c(a + j * 0x510 + i * 0x288);
        }
    }
}
