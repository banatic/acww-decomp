/* func_ov121_0229a9f8 @ 0x0229a9f8, 0xbc bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov121_02299a70(void);
extern void func_ov121_0229af7c(void *, int, int);
extern void *func_020984e8(void);
extern int func_02099fe8(void);
extern unsigned short *func_ov004_022320d8(void);
extern int func_ov121_0229a50c(void *receiver);
extern void *func_ov121_0229abac(void *, unsigned char);
extern void func_02034adc(void *, void *, int, int);
extern int func_0209a000(volatile unsigned short *, int);
extern unsigned char *func_ov121_0229afb8(void *);
extern void func_ov121_02299c88(void *, unsigned char);

void func_ov121_0229a9f8(void *obj, void *arg)
{
    volatile unsigned short h;
    int rc;
    unsigned short v0, v1;
    unsigned int hit;

    if (func_ov121_02299a70() == 0) {
        func_ov121_0229af7c(obj, 0x17, 1);
        return;
    }
    func_020984e8();
    rc = func_02099fe8();
    h = *func_ov004_022320d8();
    hit = 0;
    v0 = h;
    v1 = h;
    if (v1 >= 0x1188 && v0 <= 0x11a7) {
        hit = 1;
    }
    if (hit == 0 && rc == -1) {
        func_ov121_0229af7c(obj, 4, 1);
        return;
    }
    func_ov121_0229a50c(obj);
    func_02034adc(func_ov121_0229abac(obj, *(unsigned char *) ((char *) obj + 0xae)), arg, 1, 1);
    hit = 0;
    v0 = h;
    v1 = h;
    if (v1 >= 0x1188 && v0 <= 0x11a7) {
        hit = 1;
    }
    if (hit == 0) {
        func_0209a000(&h, 0);
    }
    func_ov121_0229afb8(obj);
    func_ov121_02299c88(obj, *(unsigned char *) ((char *) obj + 0xaf));
}
