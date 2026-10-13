/* func_02078070 @ 0x02078070, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43ec;
extern void func_0203d7d8(int a, unsigned char *p, int c);
void func_02078070(int a, int b, int c)
{
    unsigned char t[4];
    t[0] = data_021f43ec;
    t[0] = (unsigned char) b;
    func_0203d7d8(a, t, c);
}
