/* func_02067a3c @ 0x02067a3c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c1c(void *);
extern void func_02064210(char *, void *);
extern int data_021dc7a8;

int func_02067a3c(char *arg)
{
    func_020a8c1c(arg + 0x1c8c);
    func_02064210((char *) &data_021dc7a8 + 2, arg + 0x1c8c);
    return 1;
}
