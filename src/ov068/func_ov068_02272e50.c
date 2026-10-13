/* func_ov068_02272e50 @ 0x02272e50, 0x98 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_020b22b8(void);
extern int func_020b22dc(void);
extern void func_020b5e10(void);
extern void func_020b5e90(void);
extern void func_0209971c(int, unsigned short *);
extern void func_ov068_02272a7c(void *, int);

typedef struct {
    char pad_00[0x5c];
    int src1;
    int src2;
    int src3;
    char pad_68[0x2cc - 0x68];
    int dst1;
    int dst2;
    int dst3;
    char pad_2D8[0x2de - 0x2d8];
    unsigned char flag;
} UnkStruct_02272e50;

int func_ov068_02272e50(UnkStruct_02272e50 *self)
{
    int result = func_020984e8();

    self->dst1 = self->src1;
    self->dst2 = self->src2;
    self->dst3 = self->src3;

    if (func_020b22b8() != 0) {
        self->flag = 1;
        func_020b5e10();
        func_020b5e90();
        func_ov068_02272a7c(self, 1);
    } else if (func_020b22dc() != 0) {
        self->flag = 1;
        if (result != 0) {
            unsigned short local = 0xfff1;
            func_0209971c(result, &local);
        }
        func_020b5e10();
        func_020b5e90();
        func_ov068_02272a7c(self, 10);
    } else {
        func_ov068_02272a7c(self, 0);
    }

    return 1;
}
