/* func_020b6840 @ 0x020b6840, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020b64c0(int k);
extern void *data_021f42f4;
extern unsigned char data_020e54a8;
extern unsigned char data_020d2150[];

int func_020b6840(int arg)
{
    void *o;
    int res;
    unsigned short v;
    int fa;
    int fb;
    unsigned int t;

    res = 0;
    o = data_021f42f4;
    if (o != 0) {
        v = *(unsigned short *) ((char *) o + 0xc);
        fa = 1;
        fb = 1;
        t = (data_020e54a8 == 0) ? 1 : 0;
        if (t == 0) {
            t = (data_020e54a8 == 1) ? 1 : 0;
            if (t == 0) {
                fb = 0;
            }
        }
        if (fb == 0) {
            if (arg == 0 || v != 5) {
                fa = 0;
            }
        }
        if (fa != 0) {
            int k = func_020b65c4();
            if (func_020b64c0(k) != 0) {
                res = data_020d2150[k];
            }
        }
    }
    return res;
}
