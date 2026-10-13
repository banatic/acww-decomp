/* func_0204e728 @ 0x0204e728, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204ea40(void);
extern int func_020644cc(int arg);
extern void func_0209c574(void *arg);
extern void func_0204e77c(void *arg0, void *arg1);
extern int func_0204e854(void *arg);
extern int func_0204e7dc(void *arg);

void func_0204e728(void *arg0, void *arg1)
{
    int tmp;
    unsigned char *field;

    func_0204ea40();
    tmp = func_020644cc(3);

    field = (unsigned char *) arg0 + 0x2224;
    *field = (*field & ~3) | ((unsigned char) tmp & 3);

    while (1) {
        func_0209c574(arg0);
        func_0204e77c(arg0, arg1);
        if (func_0204e854(arg0) && func_0204e7dc(arg0)) {
            break;
        }
    }
}
