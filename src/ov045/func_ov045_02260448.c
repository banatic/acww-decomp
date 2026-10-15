/* func_ov045_02260448 @ 0x02260448, 0x2c bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov045_022614f0;
extern void *func_ov045_02260d34(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);

void *func_ov045_02260448(void *obj)
{
    *(void **) obj = &data_ov045_022614f0;
    func_ov045_02260d34((void *) ((char *) obj + 0x68c));
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}
