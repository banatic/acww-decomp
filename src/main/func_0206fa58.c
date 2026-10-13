/* func_0206fa58 @ 0x0206fa58, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfce8[15];
extern unsigned char data_021cfcd8[15];

void func_0206fa58(unsigned short val, unsigned short new_val)
{
    int i;
    for (i = 0; i < 15; i++) {
        if (val == data_021cfce8[i] && data_021cfcd8[i] == 0) {
            data_021cfce8[i] = new_val;
            return;
        }
    }
}
