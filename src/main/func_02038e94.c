/* func_02038e94 @ 0x02038e94, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee660(void *);
extern void func_020390a8(void *);
extern void *func_020397a0(void *);
extern void func_02039310(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020da674[];

void *func_02038e94(void *arg)
{
    func_020ee660(arg);
    *((unsigned int *) arg) = (unsigned int) data_020da13c;
    *((unsigned int *) arg) = (unsigned int) data_020da674;
    func_020390a8((char *) arg + 0x50);
    func_020397a0((char *) arg + 0x54);
    func_02039310((char *) arg + 0x358);
    return arg;
}
