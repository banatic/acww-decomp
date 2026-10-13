/* func_ov111_022a0198 @ 0x022a0198, 0x24 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229af84(void *);
extern void func_020957b4(unsigned char *);

void func_ov111_022a0198(unsigned char *s)
{
    unsigned char buf[8];
    buf[0] = func_ov095_0229af84(s + 0xac);
    func_020957b4(buf);
    s[0xa2] = 0x14;
}
