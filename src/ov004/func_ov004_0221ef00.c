/* func_ov004_0221ef00 @ 0x0221ef00, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0221f848(void *);
extern void *func_0202e5e0(void *);
extern void func_020edf54(void *);
extern char data_ov004_02253bb4[];

void *func_ov004_0221ef00(void *s)
{
    *(void **) s = &data_ov004_02253bb4;
    func_ov004_0221f848((char *) s + 0x8a8);
    func_0202e5e0(s);
    func_020edf54(s);
    return s;
}
