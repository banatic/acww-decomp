/* title_menu: 3 functions, module ov147
 * mwccarm 1.2/base -O4,s
 * func_ov147_02299374 @ 0x02299374, 0x88 bytes, Thumb
 * func_ov147_02299338 @ 0x02299338, 0x3c bytes, Thumb
 * func_ov147_02299320 @ 0x02299320, 0x18 bytes, Thumb
 */

extern void *func_020682e0(int);
extern int func_0206837c(void *);
extern int func_020ab504(int);
extern int func_020988a4(void *, int);
extern void func_020a13dc(int);
extern void *func_02094fd4(int *);
extern int func_02098844(void *, int);
extern int func_02099870(int argument0);
extern void *func_02095074(int, int *);
extern void func_02068404(void *, int, int *);
extern void *func_02094fbc(int *);
extern void func_0206844c(void *, unsigned char *, int);
extern int data_021dc7bc;
extern int data_ov147_0229a8b0;
extern int data_021ee418;
extern void *func_020900f0(void *buffer);
int func_02065ec0(int);
int func_020900f4(int *);
extern int func_0209dcac(void);
extern unsigned char data_ov147_0229a6fc[];

void func_ov147_02299374(void *receiver)
{
    void *h;
    int sel;
    int blk[8];
    unsigned char msg;
    int code;
    int n, i;
    int idx;

    h = func_020682e0(0);
    sel = func_020ab504(func_0206837c(h));
    code = 0x31;
    n = 0;
    idx = 0;
    for (i = 0; i < 4; i++) {
        if (func_020988a4(&data_021dc7bc, i) != 0) {
            if (sel == n) {
                func_020a13dc(i);
                func_02094fd4(blk);

                func_02095074(func_02099870((int) func_02098844(&data_021dc7bc, i)), blk);
                func_02068404(h, idx, blk);
                code = 4;
                func_02094fbc(blk);
            }
            n++;
        }
    }
    msg = (unsigned char) code;
    func_0206844c(h, &msg, data_ov147_0229a8b0);
}

void func_ov147_02299338(void *self)
{
    int *p = &data_021ee418;
    if (func_02065ec0((int) func_020900f0(p)) == 0) {
        return;
    }
    if (func_020900f4(p) != 0) {
        return;
    }
    {
        char c = 0x35;
        func_0206844c((void *) (*(int *) ((char *) self + 0x40)), (unsigned char *) (&c), 0);
    }
}

unsigned char func_ov147_02299320(void *receiver)
{
    return data_ov147_0229a6fc[func_0209dcac()];
}
