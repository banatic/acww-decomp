/* func_020c1848 @ 0x020c1848, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020c1b6c(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_020e7c60[];

void *func_020c1848(void *s)
{
    *(void **) s = &data_020e7c60;
    func_020c1b6c((char *) s + 0x658);
    func_0202ee5c(s);
    func_020edf54(s);
    return s;
}
