/* func_020afbcc @ 0x020afbcc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020af880(void);

void func_020afbcc(void *param)
{
    unsigned short *p;
    unsigned char *q;
    unsigned short val;
    unsigned char *r;

    func_020af880();
    p = (unsigned short *) ((char *) param + 0x5a);
    val = *p;
    val &= 0xfffff9ff;
    *p = val;
    *(int *) param = 0;
    p = (unsigned short *) ((char *) param + 0x5a);
    val = *p;
    val &= ~0x1f;
    *p = val;
    q = (unsigned char *) ((char *) param + 0x51);
    *q = 1;
    r = (unsigned char *) ((char *) param + 0x59);
    *r = 0;
}
