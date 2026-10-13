/* func_020ada48 @ 0x020ada48, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_ov004_02246378(void);
extern int func_020b65c4(void);
extern void func_020af854(void *, int, volatile unsigned short *);
extern int func_020af83c(void *, volatile unsigned short *);
extern int func_ov004_0224632c(void *, void *);
extern void *func_020984e8(void);
extern void *func_02099870(void *);
extern int func_02094ffc(void *);
extern void func_020b0200(void *);
extern void func_020adb70(int, int, int, int, int, int, int);

extern unsigned char data_021f395c[];
extern unsigned char data_021f49ec[];

void func_020ada48(void *a0, void *a1, int a2, int a3)
{
    volatile unsigned short h[2];
    unsigned short v0, v1;
    unsigned int hit;
    int idx, flag;
    unsigned int i;

    h[0] = *func_ov004_02246378();
    hit = 0;
    v0 = h[0];
    v1 = h[0];
    if (v1 >= 0x151d && v0 <= 0x151e) {
        hit = 1;
    }
    if (hit > 0 && func_020b65c4() == 0x1d) {
        h[1] = 0xfff1;
        for (i = 0; i < 0x25; i++) {
            func_020af854((void *) data_021f395c, i, &h[1]);
            hit = 0;
            v0 = h[1];
            v1 = h[1];
            if (v1 >= 0x151d && v0 <= 0x151e) {
                hit = 1;
            }
            if (hit > 0) {
                break;
            }
        }
        idx = i + func_ov004_0224632c(a0, a1);
    } else {
        idx = func_020af83c((void *) data_021f395c, &h[0]);
    }
    if (idx != -1) {
        flag = (func_02094ffc(func_02099870(func_020984e8())) == 0) ? 1 : 0;
        func_020b0200((void *) data_021f49ec);
        func_020adb70(idx, a2, a3, flag, 0, 1, 0);
    }
}
