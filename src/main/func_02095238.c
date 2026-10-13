/* func_02095238 @ 0x02095238, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642e0(void *);
extern void MI_CpuFill8(void *, int, int);

void func_02095238(void *arg0)
{
    MI_CpuFill8((char *) arg0 + 0x10, 0, 0xc);
    *(unsigned short *) ((char *) arg0 + 0xe) = 0;
    *(unsigned char *) ((char *) arg0 + 0x1c) = 2;
    func_020642e0(arg0);
}
