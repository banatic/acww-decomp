/* func_020b8c30 @ 0x020b8c30, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208aa40(void *);

void func_020b8c30(void *p)
{
    int *q = (int *) p;
    q[1] = 0;
    func_0208aa40((char *) p + 8);
    q[0x3d] = 0;
    *(unsigned short *) ((char *) p + 0xf8) = 0xfff1;
    q[0x3f] = 0;
    q[0x40] = 0;
    q[0x41] = 0;
    q[0x42] = 0;
    ((char *) p)[0x10c] = 0;
    ((char *) p)[0x10d] = 0;
}
