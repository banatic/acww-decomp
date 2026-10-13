/* func_ov003_022201e4 @ 0x022201e4, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223cef0[];

int func_ov003_022201e4(int index)
{
    if (index >= 0 && (unsigned) index < 0x20) {
        return data_ov003_0223cef0[index];
    }
    return 0;
}
