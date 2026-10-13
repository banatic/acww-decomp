/* func_02062734 @ 0x02062734, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02062870(unsigned short *p);
extern void *func_0206e6ec(void *p);
extern void *func_0206e7bc(void *p, unsigned int v);

extern unsigned char data_021cb5e0[];

int func_02062734(unsigned short *arg)
{
    unsigned int val;
    void *p, *q;
    if (func_02062870(arg) == 5) {
        val = *arg & 0xfff;
        if (val >= 0x56e) {
            val = 0x56d;
        }
        p = func_0206e6ec((void *) data_021cb5e0);
        q = func_0206e7bc(p, val);
        if (q) {
            return ((unsigned char *) q)[8];
        }
        return 0;
    }
    return -1;
}
