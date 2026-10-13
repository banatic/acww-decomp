/* func_ov004_02224da8 @ 0x02224da8, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022254ac(void *);
extern void func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov004_02254918[];

void *func_ov004_02224da8(void *s)
{
    *(void **) s = &data_ov004_02254918;
    func_ov004_022254ac((char *) s + 0x658);
    func_0202ee5c(s);
    func_020edf54(s);
    return s;
}
