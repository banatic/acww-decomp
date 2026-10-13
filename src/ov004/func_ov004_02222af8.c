/* func_ov004_02222af8 @ 0x02222af8, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02222efc(void *);
extern void func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov004_0225445c[];

void *func_ov004_02222af8(void *s)
{
    *(void **) s = &data_ov004_0225445c;
    func_ov004_02222efc((char *) s + 0x658);
    func_0202ee5c(s);
    func_020edf54(s);
    return s;
}
