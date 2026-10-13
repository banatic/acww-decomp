/* func_02067f74 @ 0x02067f74, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b45d0(void *p, unsigned int v, int n, int a, int b, int c);

void *func_02067f74(char *self)
{
    func_020b45d0(self + 0x1c30, *(unsigned int *) (self + 0x1a70), 2, 0, 0, 0);
    return self + 0x1c30;
}
