/* func_020bec14 @ 0x020bec14, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d2324[];
extern void func_020becbc(unsigned short *obj, int val, int mask, unsigned short *dst);

void func_020bec14(unsigned short *obj, int index, const unsigned short *src)
{
    unsigned short *p;
    obj[4] |= 1 << index;
    p = obj + index;
    p[5] = *src;
    func_020becbc(obj, (data_020d2324[index] >> 4) & 0xf, 0xf, p);
}
