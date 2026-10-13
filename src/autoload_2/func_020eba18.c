/* func_020eba18 @ 0x020eba18, 0x7c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int data_021fbf24;
extern int func_020ebc30(void);
extern int func_020eba94(void);

int func_020eba18(void)
{
    unsigned char b = data_021fbef8;
    data_021fbf24 = 0;
    if ((((unsigned int) b + 0xffU) & 0xffU) <= 1U) {
        return func_020ebc30();
    }
    if ((((unsigned int) b + 0xfdU) & 0xffU) <= 1U) {
        return func_020eba94();
    }
    return (b == 5) ? 0 : 0xffff;
}
