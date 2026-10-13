/* func_02055420 @ 0x02055420, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma arm
extern void func_020edb3c(void *p);
#pragma thumb

extern unsigned char data_020dd04c[];

void *func_02055420(void *p)
{
    *(unsigned int *) p = (unsigned int) data_020dd04c;
    func_020edb3c(p);
    return p;
}
