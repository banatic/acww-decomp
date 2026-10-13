/* func_02001c7c @ 0x02001c7c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe94[];
extern unsigned short data_0213fe74[];

void func_02001c7c(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    data_0213fe94[8] = a;
    data_0213fe94[9] = b;
    data_0213fe94[10] = c;
    data_0213fe94[11] = d;
    data_0213fe74[9] |= 0x40;
}
