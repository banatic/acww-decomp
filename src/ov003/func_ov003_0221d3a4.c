/* func_ov003_0221d3a4 @ 0x0221d3a4, 0x98 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0207cec0(void *, int);
extern int func_0207f1d4(void *handle);
extern int func_0207f1d8(void *);

extern unsigned char data_021e5a2c[];

int func_ov003_0221d3a4(void *p)
{
    unsigned int v;
    int idx;
    void *h;
    int ok = 0;
    v = *(unsigned short *) ((char *) p + 0x136);
    if (v >= 0x5001 && v <= 0x5008) {
        ok = 1;
    }
    if (ok) {
        idx = v - 0x5001;
    } else {
        idx = -1;
    }
    h = func_0207cec0((void *) data_021e5a2c, idx);
    if (h != 0) {
        if (func_0207f1d4(h) == 0) {
            return 0;
        }
        if (func_0207f1d8(h) == 0 || func_0207f1d8(h) == 3 || func_0207f1d8(h) == 4 || func_0207f1d8(h) == 5 ||
            func_0207f1d8(h) == 6 || func_0207f1d8(h) == 7) {
            return 0;
        }
        return 1;
    }
    return 0;
}
