/* func_020c3814 @ 0x020c3814, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void);
extern int data_021fbca0;

int func_020c3814(void)
{
    if (func_0202ec14() == 0) {
        return 0;
    } else {
        data_021fbca0 = 0;
        return 1;
    }
}
