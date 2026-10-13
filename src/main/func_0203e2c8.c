/* func_0203e2c8 @ 0x0203e2c8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e2c8(int x);

extern volatile int data_021c72c0;

int func_0203e2c8(int x)
{
    if ((data_021c72c0 & x) != 0) {
        return 1;
    } else {
        return 0;
    }
}
