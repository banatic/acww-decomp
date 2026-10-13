/* func_02078098 @ 0x02078098, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *, void *);
extern void func_020edb3c(void *);
extern unsigned char data_020e1888;

void *func_02078098(void *p)
{
    *((void **) p) = (void *) &data_020e1888;
    func_020a8c38(p, (void *) &data_020e1888);
    func_020edb3c(p);
    return p;
}
