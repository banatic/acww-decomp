/* func_02060afc @ 0x02060afc, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02060b34(unsigned short *);

void func_02060afc(void)
{
    unsigned short local;
    unsigned short *p;

    p = &local;
    *p = 0x0000fff1;
    func_02060b34(p);
}
