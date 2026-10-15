/* func_020262fc @ 0x020262fc, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02063414(volatile unsigned short *, int, int, int, int, int, int, int, int, int);
extern void *func_020984e8(void);
extern int func_020644cc(int);

void func_020262fc(unsigned short *out, int value, int object)
{
    volatile unsigned short h[2];
    unsigned short v0, v1;
    unsigned int hit;

    func_02063414(&h[0], 0x450c, 0x34, 0, 0, 0, 1, 0xa, 0, 1);
    func_02063414(&h[1], 0x450c, 0x34, 0, 0, (int) func_020984e8(), 0, 0xa, 0, 1);
    *out = 0xfff1;
    hit = 0;
    v0 = h[0];
    v1 = h[0];
    if (v1 >= 0x450c && v0 <= 0x45db) {
        hit = 1;
    }
    if (hit > 0) {
        hit = 0;
        v0 = h[1];
        v1 = h[1];
        if (v1 >= 0x450c && v0 <= 0x45db) {
            hit = 1;
        }
        if (hit > 0 && (func_020644cc(0xa) & 1) != 0) {
            *out = h[1];
        } else {
            *out = h[0];
        }
    } else {
        *out = h[1];
    }
}
