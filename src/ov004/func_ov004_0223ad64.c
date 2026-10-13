/* func_ov004_0223ad64 @ 0x0223ad64, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255fe4[];
int func_ov004_0223ad64(unsigned int i)
{
    if (i < 0xb) {
        return data_ov004_02255fe4[i];
    }
    return data_ov004_02255fe4[0];
}
