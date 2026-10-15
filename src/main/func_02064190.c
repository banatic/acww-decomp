/* func_02064190 @ 0x02064190, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020de694[];
extern void *func_020a8c38(void *p);
extern void func_020edb3c(void *p);

void *func_02064190(void *p)
{
    *(void **) p = data_020de694;
    func_020a8c38(p);
    func_020edb3c(p);
    return p;
}
