/* func_02039084 @ 0x02039084, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *p);

extern unsigned char data_020da5e8[];

void *func_02039084(void *p)
{
    *(void **) p = (void *) data_020da5e8;
    func_020edb3c(p);
    return p;
}
