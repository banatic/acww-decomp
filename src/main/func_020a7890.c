/* func_020a7890 @ 0x020a7890, 0x5a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077a34(unsigned char *, int, unsigned char *);

void func_020a7890(unsigned char *p1, int *p2, int p3, unsigned char *p4, unsigned char *p5, int *p6)
{
    unsigned char flags;

    func_02077a34(p1, p3, &flags);
    if (flags & 1) {
        *p4 = 1;
    } else {
        *p4 = 0;
    }
    if (flags & 2) {
        *p5 = 1;
    } else {
        *p5 = 0;
    }
    *p6 = p1[1] & 0x3f;
    *p2 = ((unsigned int) p1[1] >> 6) & 3;
}
