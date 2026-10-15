/* func_ov004_0222367c @ 0x0222367c, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02224580(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov004_022546e0[];

void *func_ov004_0222367c(void *s)
{
    *(void **) s = &data_ov004_022546e0;
    func_ov004_02224580((char *) s + 0x658);
    func_0202ee5c(s);
    func_020edf54(s);
    return s;
}
