/* func_02047a8c @ 0x02047a8c, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02047ac0(int a, int b, int c, int d);

void func_02047a8c(int a, int b, int count)
{
    int j, i;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < count; j++) {
            func_02047ac0(a, b, j, i);
        }
    }
}
