/* func_ov121_02299b20 @ 0x02299b20, 0xb4 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov121_02299bd4(void *);
extern void *func_020984e8(void);
extern void func_02099704(void *, volatile unsigned short *);
extern void func_020996ec(void *, volatile unsigned short *);

unsigned short func_ov121_02299b20(void *obj, int mode, unsigned short arg)
{
    volatile unsigned short h;
    unsigned short id;
    unsigned short v0, v1;
    unsigned int hit;
    void *g;

    id = func_ov121_02299bd4(obj);
    g = func_020984e8();
    h = arg;
    switch (mode) {
        case 0:
            func_02099704(g, &h);
            h = id;
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x11a8 && v0 <= 0x12a7) {
                hit = 1;
            }
            if (hit == 0) {
                id = 0xfff1;
            }
            break;
        case 1:
            func_020996ec(g, &h);
            h = id;
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x1429 && v0 <= 0x1430) {
                hit = 1;
            }
            if (hit > 0) {
                id = 0xfff1;
            }
            break;
        case 2:
            h = id;
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x13a0 && v0 <= 0x13a7) {
                hit = 1;
            }
            if (hit > 0) {
                id = 0xfff1;
            }
            break;
    }
    return id;
}
