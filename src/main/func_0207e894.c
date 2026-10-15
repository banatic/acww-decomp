/* func_0207e894 @ 0x0207e894, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020996f8(int);
extern int func_0204bcdc(void *);
extern int func_0204bc64(const void *p);

int func_0207e894(int v)
{
    unsigned short local;
    void *p;
    int w;

    p = func_020996f8(v);
    if (func_0204bcdc(p) != 0) {
        local = 0x13E3;
        v = func_0204bc64(p);
        w = func_0204bc64(&local);
        if (v == w) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*(unsigned short *) p == 0x13E3) {
            return 1;
        } else {
            return 0;
        }
    }
}
