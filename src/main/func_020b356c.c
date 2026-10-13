/* func_020b356c @ 0x020b356c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e50dc;
extern void func_020b3740(void *);

void *func_020b356c(void *self)
{
    unsigned int i;
    *(int *) self = (int) &data_020e50dc;
    func_020b3740((char *) self + 8);
    for (i = 0; i < 3; i++) {
        ((signed char *) self + i)[4] = -1;
    }
    return self;
}
