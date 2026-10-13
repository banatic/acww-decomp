/* func_ov004_0221ad40 @ 0x0221ad40, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02257804[];

int func_ov004_0221ad40(int index)
{
    if (index >= 0 && (unsigned) index < 0x40) {
        return data_ov004_02257804[index];
    }
    return 0;
}
