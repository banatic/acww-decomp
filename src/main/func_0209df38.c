/* func_0209df38 @ 0x0209df38, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021dc754[3];
extern unsigned int data_021dc744[3];

void func_0209df38(unsigned char *p)
{
    unsigned int *const b = data_021dc754;
    unsigned int *a = data_021dc744;

    *(unsigned int *) p = 0;
    *(unsigned int *) (p + 4) = 0;
    p[5] = (unsigned char) a[0];
    p[4] = (unsigned char) a[1];
    p[3] = (unsigned char) a[2];
    p[2] = (unsigned char) b[0];
    p[1] = (unsigned char) b[1];
    p[0] = (unsigned char) b[2];
}
