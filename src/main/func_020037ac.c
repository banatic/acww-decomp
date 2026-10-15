/* func_020037ac @ 0x020037ac, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642bc(void *, const void *);

void func_020037ac(unsigned char *r5, unsigned char *r4)
{
    func_020642bc(r5, r4);
    r5[0xf] = r4[0xf];
    r5[0xe] = r4[0xe];
}
