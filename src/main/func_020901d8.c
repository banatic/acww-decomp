/* func_020901d8 @ 0x020901d8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066694(void *);
extern int func_020b1a64(void *);
extern int func_02079914(void *);
extern int func_02088460(void *);

void *func_020901d8(void *arg)
{
    func_02066694(arg);
    func_020b1a64((char *) arg + 0x100);
    func_02079914((char *) arg + 0x14c);
    func_02088460((char *) arg + 0x93a);
    return arg;
}
