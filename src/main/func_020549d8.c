/* func_020549d8 @ 0x020549d8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056aa0(void *addr, int arg);

void func_020549d8(void *self, int arg)
{
    if (*(int *) ((char *) self + 0x148) != 0) {
        func_02056aa0((char *) self + 0x110, arg);
    }
}
