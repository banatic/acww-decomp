/* func_020a19c0 @ 0x020a19c0, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a1368(void *p);
extern int func_02050974(void *p);
extern void func_02050948(void *p);
extern void func_020509a8(void *a, void *b, int c, int d);
extern int func_02050920(void *a, int b);

extern int data_020d1c20[];
extern int data_020d1bf0[];
extern int data_020d1c08[];
extern char data_021dc7a8[];
extern char data_021c8188[];

int func_020a19c0(int unused, int idx)
{
    void *local[3];
    void *p;
    int v, a, b;

    local[0] = data_021dc7a8;
    local[1] = data_021dc7a8;
    local[2] = func_020a1368(data_021dc7a8);

    p = local[idx];
    v = func_02050974(data_021c8188);
    a = data_020d1c20[idx];
    b = data_020d1bf0[idx];

    if (v == 4) {
        func_020509a8(data_021c8188, p, b, a);
    } else if (v == 1) {
        func_02050948(data_021c8188);
        return 1;
    } else if (v == 3) {
        // nothing
    } else {
        func_02050948(data_021c8188);
        if (func_02050920(p, data_020d1c08[idx]) == 0) {
            return 0;
        } else {
            return 4;
        }
    }
    return 3;
}
