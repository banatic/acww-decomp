/* func_ov050_02262eec @ 0x02262eec, 0x5c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov050_02263394(void *a, void *b);
extern void func_020984e8(void);
extern int func_02099640(void);
extern void func_0209ad9c(int a, int b);
extern void func_0209b4d4(void);
extern int func_0209bba0(void);

typedef struct {
    char pad_00[0xb4];
    unsigned char *ptr;
} Arg0;

typedef struct {
    char pad_00[4];
    unsigned char flag;
} Arg1;

void func_ov050_02262eec(Arg0 *arg0, Arg1 *arg1)
{
    if (func_ov050_02263394(arg0, arg1) != 0) {
        return;
    }

    func_020984e8();
    func_0209ad9c(func_02099640(), 0);
    func_0209b4d4();

    if (func_0209bba0() == 1) {
        arg1->flag = 0x2c;
    } else {
        if (arg0->ptr[0x73e] == 0) {
            arg1->flag = 0x2b;
            arg0->ptr[0x73e] = 1;
        } else {
            arg1->flag = 0x10;
        }
    }
}
