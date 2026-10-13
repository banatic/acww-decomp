/* func_02019cc8 @ 0x02019cc8, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019d0c(void *self, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);

int func_02019cc8(void *self, int p1, int p2, int p3, int p5, unsigned short p6)
{
    int result = 0;
    if (func_02019d0c(self, 7, p1, 0, 0, (short) p2, (short) p3, 0, 0, p6, 0)) {
        *(int *) ((char *) self + 0x40) = p5;
        result = 1;
    }
    return result;
}
