/* func_02001d60 @ 0x02001d60, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe94[0x12];
extern void func_02001d28(int param);

void func_02001d60(unsigned char param0, int param1)
{
    data_0213fe94[0x11] = param0;
    func_02001d28(param1);
}
