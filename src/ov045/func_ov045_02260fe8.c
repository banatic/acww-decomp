/* func_ov045_02260fe8 @ 0x02260fe8, 0x4c bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *p);
extern void func_ov045_02260e50(void *p, int x);
extern void *data_ov045_022615a0;

int func_ov045_02260fe8(void *p)
{
    if (func_0202ec58(p) == 0) {
        return 0;
    }

    data_ov045_022615a0 = p;
    func_ov045_02260e50(p, 0);

    *((unsigned int *) ((char *) p + 0x4e8)) |= 2;
    *((unsigned char *) p + 0x744) = 0xff;
    *((unsigned char *) p + 0x745) = 0xff;

    return 1;
}
