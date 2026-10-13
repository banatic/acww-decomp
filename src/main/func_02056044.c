/* func_02056044 @ 0x02056044, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020563c0(void *p);
extern void func_02055fcc(void *p);
extern char data_020dd13c;

void *func_02056044(void *p)
{
    func_020563c0(p);
    *(void **) p = &data_020dd13c;
    func_02055fcc(p);
    return p;
}
