/* func_020ed73c @ 0x020ed73c, 0x60 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int func_020ed834(int a0, int a1, int a2, unsigned int argument3);
extern int func_020ed79c(int a0, int a1, int a2, int a3);

int func_020ed73c(int a0, int a1, int a2, int a3)
{
    if ((unsigned char) (data_021fbef8 + 0xff) <= 1) {
        return func_020ed834(a0, a1, a2, a3);
    }
    if ((unsigned char) (data_021fbef8 + 0xfd) <= 1) {
        return func_020ed79c(a0, a1, a2, a3);
    }
    return 0;
}
