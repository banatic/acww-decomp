/* func_020a5254 @ 0x020a5254, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e3c94;
extern unsigned char data_020da13c;
extern void func_020ee62c(void *);

void *func_020a5254(void *r0)
{
    unsigned char *volatile *p = (unsigned char *volatile *) r0;
    *p = &data_020e3c94;
    *p = &data_020da13c;
    func_020ee62c(r0);
    return r0;
}
