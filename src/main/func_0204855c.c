/* func_0204855c @ 0x0204855c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void func_02048594(int, int, int, int);

extern unsigned char data_021c79c4[];

void func_0204855c(int r0, int r1, int r2, int r3)
{
    int *ptr;
    int a, b, c, d;

    ptr = (int *) data_021c79c4;
    if (*ptr == 4) {
        if (func_020644cc(100) < 50) {
            a = r0;
            b = r1;
            c = r2;
            d = r3;
            func_02048594(a, b, c, d);
        }
    }
}
