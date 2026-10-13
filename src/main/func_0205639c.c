/* func_0205639c @ 0x0205639c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *p);

extern unsigned char data_020dd11c[];

void *func_0205639c(void *p)
{
    *(unsigned int *) p = (unsigned int) data_020dd11c;
    func_020edb3c(p);
    return p;
}
