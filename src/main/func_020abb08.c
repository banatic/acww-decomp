/* func_020abb08 @ 0x020abb08, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020aca48(void *);
extern void func_020abc6c(void *, int);

void func_020abb08(void *arg0)
{
    *(int *) ((char *) arg0 + 0x13c) = 5;
    func_020aca48((char *) arg0 + 0xe4);
    func_020abc6c(arg0, 3);
}
