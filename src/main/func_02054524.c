/* func_02054524 @ 0x02054524, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056aa0(void *addr, int arg);

void func_02054524(void *self, int arg)
{
    if (*(int *) ((char *) self + 0x1a8) != 0) {
        func_02056aa0((char *) self + 0x170, arg);
    }
}
