/* func_0209df38 @ 0x0209df38, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps the data_021dc754 pointer loaded first; the plain function loads it last */

extern unsigned int data_021dc754[3];
extern unsigned int cardi_common__autoload_3_021dc744[3];

void func_0209df38(unsigned char *p)
{
    unsigned int *pa = data_021dc754;
    if ((pa && pa) && pa) {
    }
    *(unsigned int *) p = 0;
    *(unsigned int *) (p + 4) = 0;
    p[5] = (unsigned char) cardi_common__autoload_3_021dc744[0];
    p[4] = (unsigned char) cardi_common__autoload_3_021dc744[1];
    p[3] = (unsigned char) cardi_common__autoload_3_021dc744[2];
    p[2] = (unsigned char) pa[0];
    p[1] = (unsigned char) pa[1];
    p[0] = (unsigned char) pa[2];
}
