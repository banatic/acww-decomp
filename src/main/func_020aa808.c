/* func_020aa808 @ 0x020aa808, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *this);

extern unsigned char data_020e408c[];

void *func_020aa808(void *arg)
{
    *(unsigned int *) arg = (unsigned int) data_020e408c;
    func_020edb3c(arg);
    return arg;
}
