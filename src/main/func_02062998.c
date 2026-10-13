/* func_02062998 @ 0x02062998, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *arg);
extern void *func_0206e7bc(void *arg, unsigned int val);

extern unsigned char data_021cb5e0[];

unsigned char func_02062998(void *ptr)
{
    unsigned int v;
    void *p;
    void *q;

    v = (*(unsigned short *) ptr) & 0xFFF;
    if (v >= 0x56e) {
        v = 0x56d;
    }
    p = func_0206e6ec((void *) data_021cb5e0);
    q = func_0206e7bc(p, v);
    if (q) {
        return ((unsigned char *) q)[5];
    }
    return 0;
}
