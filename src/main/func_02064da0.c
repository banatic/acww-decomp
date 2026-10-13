/* func_02064da0 @ 0x02064da0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021cd87c[];
extern unsigned int data_021cd888[];

void func_02064da0(unsigned int idx, unsigned int value)
{
    data_021cd87c[idx] = 0;
    data_021cd888[idx] = value;
}
