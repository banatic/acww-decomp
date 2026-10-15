/* func_ov004_0221ffec @ 0x0221ffec, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02220d24(void *);
extern void *func_0202e5e0(void *);
extern void func_020edf54(void *);
extern char data_ov004_02253e10[];

void *func_ov004_0221ffec(void *s)
{
    *(void **) s = &data_ov004_02253e10;
    func_ov004_02220d24((char *) s + 0x918);
    func_0202e5e0(s);
    func_020edf54(s);
    return s;
}
