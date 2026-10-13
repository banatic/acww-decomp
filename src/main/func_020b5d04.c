/* func_020b5d04 @ 0x020b5d04, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e5574;
extern char data_020e3c94;
extern char data_020da13c;
extern void func_020ee62c(void *);

void *func_020b5d04(void *p)
{
    *(void **) p = &data_020e5574;
    *(void **) p = &data_020e3c94;
    *(void **) p = &data_020da13c;
    func_020ee62c(p);
    return p;
}
