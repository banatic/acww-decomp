/* func_0204ca8c @ 0x0204ca8c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern unsigned char data_021f3a08[];
extern int func_02073d90(int);

void func_0204ca8c(unsigned int param)
{
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    if (param >= 0x17) {
        param = 0x16;
    }
    data_021f3a08[0x17] = (unsigned char) param;
}
