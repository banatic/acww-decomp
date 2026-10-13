/* func_02064db8 @ 0x02064db8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021cd87c[];
extern int data_021cd888[];
extern int data_021cd880[];

void func_02064db8(int index, int value1, int value2)
{
    data_021cd87c[index] = 1;
    data_021cd888[index] = value1;
    data_021cd880[index] = value2;
}
