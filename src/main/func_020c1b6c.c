/* func_020c1b6c @ 0x020c1b6c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *);
extern char data_020e7bd0;

void *func_020c1b6c(void *p)
{
    *(void **) p = (void *) &data_020e7bd0;
    func_0202eb20(p);
    return p;
}
