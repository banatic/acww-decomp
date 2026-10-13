/* func_02008750 @ 0x02008750, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

int func_02008750(char *arg0, unsigned short *arg1, int arg2, int arg3)
{
    char local[0x1c];
    int result;

    func_0200e92c(local);
    func_0200e90c(local, 0x85, arg2, arg3);
    *(unsigned short *) (arg0 + 0x822) = *arg1;
    *(unsigned short *) (arg0 + 0x820) = *(unsigned short *) (arg0 + 0x822);
    result = func_0200e894(arg0, local);
    func_0200e91c(local);
    return result;
}
