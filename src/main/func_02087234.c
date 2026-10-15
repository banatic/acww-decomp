/* func_02087234 @ 0x02087234, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02095238(void *);

void func_02087234(unsigned short *r4)
{
    unsigned short value;
    value = 0x0000fff1;
    func_02095238(r4);
    r4[0x0f] = value;
}
