/* func_020b27d4 @ 0x020b27d4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cec0(int address, int param);
extern int func_0207f1d8(void);
extern int data_021e5a2c;

int func_020b27d4(int param)
{
    if (func_0207cec0((int) &data_021e5a2c, param) != 0) {
        if (func_0207f1d8() != 2) {
            return 0;
        }
        return 1;
    }
    return 0;
}
