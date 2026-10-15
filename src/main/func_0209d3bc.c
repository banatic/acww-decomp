/* func_0209d3bc @ 0x0209d3bc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021dc6cc[];
int func_0209d3bc(unsigned int index, unsigned int value)
{
    if (index < 3) {
        data_021dc6cc[index] = value;
        return 1;
    } else {
        return 0;
    }
}
