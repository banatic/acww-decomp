/* func_020629ec @ 0x020629ec, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *);
extern void *func_0206e7bc(void *, unsigned int);

extern unsigned char data_021cb5e0[];

unsigned short func_020629ec(void *param)
{
    void *p;
    void *ret;
    unsigned int val;

    val = *(unsigned short *) param & 0x0fff;
    if (val >= 0x56e) {
        val = 0x56d;
    }
    p = func_0206e6ec((void *) data_021cb5e0);
    ret = func_0206e7bc(p, val);
    if (ret != 0) {
        return *(unsigned short *) ((unsigned char *) ret + 2);
    }
    return 0;
}
