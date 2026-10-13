/* func_0206826c @ 0x0206826c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cda88;
void func_02138c00(int a, int b, int c, void (*cb)(void));
void func_020684b0(void);

void func_0206826c(void)
{
    if (data_021cda88 != 0) {
        func_02138c00(data_021cda88, 0x1e9c, 8, func_020684b0);
        data_021cda88 = 0;
    }
}
