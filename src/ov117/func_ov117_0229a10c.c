/* func_ov117_0229a10c @ 0x0229a10c, 0x88 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0207cec0(void *base, int idx);
extern unsigned char *func_020800d0(void *p);
extern int func_02081f80(void *p);
extern unsigned short func_0204bbbc(int i);
extern int func_020b3b50(unsigned short *h);
extern void func_020b3c58(int flag, int *v0, int *v1, int *v2, int *v3);
extern void func_ov117_0229a2a4(void *param, int a, int b, int c, int d);

extern unsigned char data_021e5a2c[];

void func_ov117_0229a10c(void *param)
{
    int i;
    int x, y;
    int d = 0;
    void *obj;
    unsigned short h;
    int v0, v1, v2, v3;
    int flag;
    unsigned char b0, b1;
    for (i = 0; i < 8; i++) {
        obj = func_0207cec0((void *) data_021e5a2c, i);
        if (func_02081f80(func_020800d0(obj))) {
            h = func_0204bbbc(i);
            b0 = func_020800d0(obj)[0];
            b1 = func_020800d0(obj)[1];
            x = b0 * 2;
            y = b1 * 2;
            x += 1;
            y += 1;
            flag = func_020b3b50(&h);
            if (flag) {
                func_020b3c58(flag, &v0, &v1, &v2, &v3);
                x += (v0 >> 11);
                y += (v1 >> 11);
            }
            func_ov117_0229a2a4(param, i + 3, x, y, d);
        }
    }
}
