/* func_ov147_02299b4c @ 0x02299b4c, 0x44 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020682e0(int);
extern void func_02068320(void *);
extern void *func_020b5e10(void);
extern int func_020b6434(void *, int, int, int);
extern void func_ov147_0229a01c(void *);
extern unsigned char data_021c75b8;

void func_ov147_02299b4c(void *self)
{
    void *a;
    unsigned int cond;

    a = func_020682e0(0);
    cond = (data_021c75b8 == 2);
    if (cond != 0) {
        if (*(int *) ((char *) a + 4) == 0) {
            void *c;

            func_02068320(a);
            c = func_020b5e10();
            func_020b6434(c, 0x30, 2, 2);
            func_ov147_0229a01c(self);
        }
    }
}
