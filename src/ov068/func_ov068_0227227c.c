/* func_ov068_0227227c @ 0x0227227c, 0x88 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_02262ed4(void *, int);
extern void *func_02056f94(void *);
extern void func_ov068_02272a7c(void *, int);
extern void func_ov068_02272c64(void *);
extern void func_02055124(void *);
extern void *func_020961a8(int);
extern int func_ov068_02272cd4(void *);
extern int func_020e8b4c(int, int);
extern void func_02095518(int, int, int);

void func_ov068_0227227c(void *param)
{
    void *p;
    short v;

    func_ov009_02262ed4((char *) param + 0x238, 0x888);
    if (func_02056f94((char *) param + 0x1d8) != 0) {
        func_ov068_02272a7c(param, 0xd);
    }
    func_ov068_02272c64(param);
    func_02055124((char *) param + 0x13c);
    p = func_020961a8(4);
    if (p) {
        v = *(short *) ((char *) p + 0x8e);
        if (func_020e8b4c(v, func_ov068_02272cd4(param)) < 0x1200) {
            func_02095518(0, (short) (func_ov068_02272cd4(param) - v), 4);
        }
    }
}
