/* func_020a9c04 @ 0x020a9c04, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);
extern void func_020edf54(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3e8c[];

void *func_020a9c04(void *arg)
{
    *(unsigned int *) arg = (unsigned int) data_020e3e8c;
    *(unsigned int *) arg = (unsigned int) data_020da13c;
    func_020ee62c(arg);
    func_020edf54(arg);
    return arg;
}
