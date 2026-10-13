/* func_02062780 @ 0x02062780, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021cb5e0;
extern void *func_0206e6ec(void *);
extern void *func_0206e7bc(void *, unsigned int);

unsigned char func_02062780(unsigned short *src)
{
    unsigned int val;
    void *p;
    unsigned char *q;

    val = *src & 0xFFF;
    if (val >= 0x56E) {
        val = 0x56D;
    }
    p = func_0206e6ec(&data_021cb5e0);
    q = (unsigned char *) func_0206e7bc(p, val);
    if (q != 0) {
        return q[7];
    }
    return 0;
}
