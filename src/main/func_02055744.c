/* func_02055744 @ 0x02055744, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02055ff4(void *p);
extern void func_020edb3c(void *p);

extern unsigned char data_020dd03c[];

void *func_02055744(void *p)
{
    *(void **) p = (void *) data_020dd03c;
    func_02055ff4(p);
    func_020edb3c(p);
    return p;
}
