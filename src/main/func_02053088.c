/* func_02053088 @ 0x02053088, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02053358(void *p);
extern void func_020532d0(void *p);

void func_02053088(void *p)
{
    unsigned int i;

    i = 0;
    do {
        func_02053358((char *) p + (i << 5));
        i++;
    } while (i < 2);
    func_020532d0((char *) p + 0x40);
}
