/* func_ov004_02221878 @ 0x02221878, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02221994(void *);
extern void *func_0202e5e0(void *);
extern void func_020edf54(void *);
extern char data_ov004_02253fd4[];

void *func_ov004_02221878(void *s)
{
    *(void **) s = &data_ov004_02253fd4;
    func_ov004_02221994((char *) s + 0x89c);
    func_0202e5e0(s);
    func_020edf54(s);
    return s;
}
