/* func_0208c688 @ 0x0208c688, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208c3b8(void *);

void func_0208c688(void *param)
{
    unsigned char *p1;
    unsigned int *p2;
    unsigned int *p3;
    unsigned int *p4;
    unsigned int *p5;

    p1 = (unsigned char *) ((char *) param + 0xd4);
    *p1 = 0;

    p2 = (unsigned int *) ((char *) param + 0xc4);
    *p2 = 0;

    p3 = (unsigned int *) ((char *) param + 0xc8);
    *p3 = 0;

    p4 = (unsigned int *) ((char *) param + 0xcc);
    *p4 = 0;

    p5 = (unsigned int *) ((char *) param + 0xd0);
    *p5 = 0;

    func_0208c3b8(param);
}
