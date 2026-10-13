/* func_ov147_02299c34 @ 0x02299c34, 0x44 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75b8;

typedef struct {
    int pad_00;
    int unk_04;
} Work;

extern void *func_020682e0(int);
extern void func_02068320(void *);
extern int func_020b5e10(void);
extern void func_020b6434(int, int, int, int);
extern void func_ov147_0229a01c(void *);

void func_ov147_02299c34(void *a)
{
    Work *p;
    unsigned int cond;
    p = (Work *) func_020682e0(0);
    cond = (data_021c75b8 == 2);
    if (cond && p->unk_04 == 0) {
        func_02068320(p);
        func_020b6434(func_020b5e10(), 6, 2, 2);
        func_ov147_0229a01c(a);
    }
}
