/* func_ov004_0221d220 @ 0x0221d220, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e1dc(void);
extern int data_ov004_02257a18;

int func_ov004_0221d220(void)
{
    if (func_0202e1dc() == 0) {
        return 0;
    } else {
        data_ov004_02257a18 = 0;
        return 1;
    }
}
