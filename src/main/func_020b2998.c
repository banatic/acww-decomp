/* func_020b2998 @ 0x020b2998, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern int data_021f4b50;

int func_020b2998(void)
{
    if (func_020b6660() == 0) {
        return 1;
    }
    if (data_021f4b50 == 0) {
        return 0;
    }
    return 1;
}
