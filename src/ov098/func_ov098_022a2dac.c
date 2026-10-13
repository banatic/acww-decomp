/* func_ov098_022a2dac @ 0x022a2dac, 0x48 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *p, int a, int b);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, const void *buf, int len);
extern void func_02073770(void *p, int a, int b);

void func_ov098_022a2dac(int arg0, int arg1, int arg2)
{
    if (func_02073d90(data_020ccf94, arg1, arg2)) {
        unsigned char buf[3];
        void *ctx;
        buf[0] = 1;
        buf[1] = arg1;
        buf[2] = arg2;
        ctx = data_020ccf94;
        func_02073820(ctx);
        func_020737f0(ctx, buf, 3);
        func_02073770(ctx, 0x16, 4);
    }
}
