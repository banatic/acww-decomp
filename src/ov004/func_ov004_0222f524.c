/* func_ov004_0222f524 @ 0x0222f524, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c8c9c;
extern int func_0206fbc0(void);
extern void func_ov004_0222f6e8(char *self, int a);
void func_ov004_0222f524(char *self)
{
    if (data_021c8c9c == 0 && func_0206fbc0() != 0) {
        func_ov004_0222f6e8(self, 5);
    }
}
