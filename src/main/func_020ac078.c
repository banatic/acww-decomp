/* func_020ac078 @ 0x020ac078, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020acb70(void *a);
extern void func_0208f4e0(void *a);
extern void func_020ac9ec(void *a);
extern void func_020ac954(void *a);

extern unsigned char data_020e3fe4[];

void *func_020ac078(void *arg)
{
    *(void **) arg = (void *) data_020e3fe4;
    func_020acb70((void *) ((char *) arg + 0xE4));
    func_0208f4e0((void *) ((char *) arg + 0x6C));
    func_020ac9ec((void *) ((char *) arg + 0x20));
    func_020ac954(arg);
    return arg;
}
