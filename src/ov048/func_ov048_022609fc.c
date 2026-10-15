/* func_ov048_022609fc @ 0x022609fc, 0x28 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073918(int, int);
extern int data_020ccf94;

unsigned char func_ov048_022609fc(void *receiver)
{
    int val;
    if (func_02073918(data_020ccf94, 0) != 0) {
        val = 0x21;
    } else {
        val = 0x22;
    }
    return (unsigned char) val;
}
