/* func_02055ff4 @ 0x02055ff4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056390(void *);

extern unsigned char data_020dd13c[];

void *func_02055ff4(void *p)
{
    *(void **) p = (void *) data_020dd13c;
    func_02056390(p);
    return p;
}
