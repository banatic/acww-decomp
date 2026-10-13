/* func_0203a454 @ 0x0203a454, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *, void *);

extern unsigned char data_020da6c4[];

void *func_0203a454(void *p)
{
    void *x;
    x = (void *) data_020da6c4;
    *(void **) p = x;
    func_020edb3c(p, x);
    return p;
}
