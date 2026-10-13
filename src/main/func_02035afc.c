/* func_02035afc @ 0x02035afc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *p);

extern unsigned char data_020da2b4[];

void *func_02035afc(void *p)
{
    *(void **) p = (void *) data_020da2b4;
    func_020edb3c(p);
    return p;
}
