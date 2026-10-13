/* func_020ac96c @ 0x020ac96c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3fb4;
extern void func_020ac8a8(void *p);
extern void func_020edb3c(void *p);

void *func_020ac96c(void *p)
{
    *(void **) p = (void *) &data_020e3fb4;
    func_020ac8a8(p);
    func_020edb3c(p);
    return p;
}
