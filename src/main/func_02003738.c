/* func_02003738 @ 0x02003738, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642e0(void *);

void func_02003738(unsigned char *r4)
{
    func_020642e0(r4);
    r4[0xf] = 0xff;
    r4[0xe] = 6;
}
