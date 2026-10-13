/* func_ov083_02278f38 @ 0x02278f38, 0x80 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *);
extern void func_ov083_02278e98(void *, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02054188(void *, int, int);
extern int func_0203fdc4(int);
extern void func_020865d8(int, int);

extern unsigned char data_021f3aa4[];

int func_ov083_02278f38(void *p)
{
    if (func_0202ec58(p) == 0) {
        return 0;
    }
    func_ov083_02278e98(p, 0);
    func_02016764((char *) p + 0x334, p, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188((char *) p + 0xec, 0xc, 0xe);
    *(unsigned int *) ((char *) p + 0x4e8) |= 2;
    *((unsigned char *) p + 0x718) = (unsigned char) func_0203fdc4(0xe);
    func_020865d8((unsigned int) data_021f3aa4, 0);
    return 1;
}
