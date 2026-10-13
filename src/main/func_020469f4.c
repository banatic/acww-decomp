/* func_020469f4 @ 0x020469f4, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void *data_020ccf94;
extern unsigned char data_021f39fc[];
extern char data_021c779c[];

extern int func_02041718(void);
extern int func_02073d90(void *);
extern void func_0209e474(void *);
extern int func_0209e350(void *dst, void *src);
extern int _s32_div_f(int a, int b);
extern void func_0204130c(int a, int b, int c);
extern void func_02046f7c(void *p);

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

void func_020469f4(void)
{
    Pair a;
    Pair b;

    if (func_02041718() != 0) {
        if (func_02073d90(data_020ccf94) == 0) {
            unsigned char *g;
            a.unk_00 = 0;
            a.w1 = 0;
            b.unk_00 = 0;
            b.w1 = 0;
            g = data_021f39fc;
            func_0209e474(&a);
            b.unk_00 = 0;
            b.w1 = 0;
            ((unsigned char *) &b)[5] = g[2];
            ((unsigned char *) &b)[4] = g[1];
            ((unsigned char *) &b)[3] = g[0];
            ((unsigned char *) &b)[2] = 6;
            if (_s32_div_f(_s32_div_f(func_0209e350(&b, &a), 0x3c), 0x18) >= 1) {
                func_0204130c(-1, 0x63, 0);
            }
        }
        func_02046f7c(data_021c779c);
    }
}
