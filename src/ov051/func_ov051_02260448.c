/* func_ov051_02260448 @ 0x02260448, 0x2c bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov051_0226193c;
extern void *func_ov051_02261058(char *p);
extern void *func_0202ee5c(char *p);
extern void func_020edf54(char *p);

char *func_ov051_02260448(char *p)
{
    *(char **) p = &data_ov051_0226193c;
    func_ov051_02261058(p + 0x658);
    func_0202ee5c(p);
    func_020edf54(p);
    return p;
}
