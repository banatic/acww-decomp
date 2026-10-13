/* func_020b727c @ 0x020b727c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *, void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5764[];

void *func_020b727c(void *p)
{
    void *val;
    val = (void *) data_020e5764;
    *(void *volatile *) p = val;
    val = (void *) data_020e3c94;
    *(void *volatile *) p = val;
    val = (void *) data_020da13c;
    *(void *volatile *) p = val;
    func_020ee62c(p, val);
    return p;
}
