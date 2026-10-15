/* func_ov147_02299be8 @ 0x02299be8, 0x44 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} Res;

extern unsigned char data_021c75b8;
extern Res *func_020682e0(int);
extern void func_02068320(Res *);
extern int func_020b5e10(void);
extern int func_020b6434(int, int, int, int);
extern void func_ov147_0229a01c(void *);

void func_ov147_02299be8(void *self)
{
    Res *res;
    unsigned int flag;

    flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag > 0) {
        res = func_020682e0(0);
        if (res->unk_04 == 0) {
            func_02068320(res);
            func_020b6434(func_020b5e10(), 0x2d, 2, 0);
            func_ov147_0229a01c(self);
        }
    }
}
