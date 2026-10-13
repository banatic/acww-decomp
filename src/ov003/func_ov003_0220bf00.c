/* func_ov003_0220bf00 @ 0x0220bf00, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223c5f4[];

int func_ov003_0220bf00(int index)
{
    if (index >= 0 && index < 8) {
        return data_ov003_0223c5f4[index];
    }
    return 0;
}
