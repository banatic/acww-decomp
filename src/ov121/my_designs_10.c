/* my_designs_10: 5 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229b9d8 @ 0x0229b9d8, 0x8 bytes, Thumb
 * func_ov121_0229b9d4 @ 0x0229b9d4, 0x2 bytes, Thumb
 * func_ov121_0229b968 @ 0x0229b968, 0x6c bytes, Thumb
 * func_ov121_0229b948 @ 0x0229b948, 0x1e bytes, Thumb
 * func_ov121_0229b8c0 @ 0x0229b8c0, 0x88 bytes, Thumb
 */

extern void func_ov121_02299c10(void *);
extern int func_ov121_02299a5c(void *, int);
extern int func_020b9bbc(void *, void *, int, int, int);
extern void func_ov121_02299a3c(void *, int);
extern int func_ov002_02207d5c(void *);
extern void func_ov121_0229a480(void *);
extern void func_ov002_022091cc(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern int func_02002d14(int, int, int, int, int, int);
extern int func_02002c6c(int, int, int, int, int, int);
extern int func_02064af4(int, int, int);
extern int func_ov121_0229adac(int, int);
extern void func_ov121_0229af00(int, int, int);
extern void func_ov121_02299a4c(int, int);
extern unsigned int data_021fbe94;
extern int data_ov121_0229c438;
extern int data_ov121_0229c450;
extern int data_ov121_0229c468;

void func_ov121_0229b968(char *param);

void func_ov121_0229b9d8(char *arg0)
{
    func_ov121_0229b968((char *) arg0);
}

void func_ov121_0229b9d4(void *receiver) {}

void func_ov121_0229b968(char *param)
{
    func_ov121_02299c10(param);
    if (func_ov121_02299a5c(param, 2)) {
        if (func_020b9bbc(param + 0x91c, param + 0x98c, 6, 0x800, 0)) {
            func_ov121_02299a3c(param, 2);
        }
    }
    if (func_ov002_02207d5c(param + 0x2d8)) {
        func_ov121_0229a480(param);
    }
    func_ov002_022091cc(param + 0x528);
}

void func_ov121_0229b948(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
}

void func_ov121_0229b8c0(int param)
{
    unsigned int tmp = data_021fbe94;
    unsigned char i;
    int seven = 7;

    func_02002d14((int) &data_ov121_0229c438, tmp, 6, 1, 1, 7);
    func_02002c6c((int) &data_ov121_0229c450, tmp, 6, 0x10, 0x10, 0xc5);
    func_02064af4((int) &data_ov121_0229c468, param + 0x98c, 0x800);

    i = 9;
    do {
        if (func_ov121_0229adac(param, i) != 0) {
            func_ov121_0229af00(param, i, seven);
        }
        i++;
    } while (i <= 15);

    func_ov121_02299a4c(param, 2);
}
