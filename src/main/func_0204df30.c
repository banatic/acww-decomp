/* func_0204df30 @ 0x0204df30, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060f30(int);
extern int data_021c80e0[];

int func_0204df30(int param)
{
    int result = 0;
    if (func_02060f30(param)) {
        result = data_021c80e0[param];
    }
    return result;
}
