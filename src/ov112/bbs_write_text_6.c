/* bbs_write_text_6: 2 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_0229f900 @ 0x0229f900, 0x2c bytes, Thumb
 * func_ov112_0229f8e4 @ 0x0229f8e4, 0x1c bytes, Thumb
 */

extern int func_ov112_0229fe70(void *p, int a);
extern void func_ov112_0229fe50(void *obj, int arg1);

int func_ov112_0229f900(unsigned char *p0)
{
    if ((func_ov112_0229fe70(p0, 0x100) == 0) || (p0[0xbe] == p0[0xbf])) {
        return 0;
    }
    return 1;
}

void func_ov112_0229f8e4(void *obj)
{
    ((char *) obj)[0xbe] = 0;
    ((char *) obj)[0xbf] = 0;
    func_ov112_0229fe50(obj, 0x100);
}
