/* func_ov121_0229af40 @ 0x0229af40, 0x18 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov121_0229c238[];

int func_ov121_0229af40(int unused, unsigned int index)
{
    if (index >= 0x10 && index <= 0x17) {
        return 8;
    } else {
        return data_ov121_0229c238[index];
    }
}
