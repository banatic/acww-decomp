/* func_ov110_0229e05c @ 0x0229e05c, 0x9c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_ov110_0229e7ac(void *receiver);
extern void func_ov110_0229c8f4(void *p);
extern int func_ov002_02208054(void *p, int a);
extern int func_ov002_02208b00(void *p, int b1, int b2);
extern void func_ov002_02209114(void *p, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov110_0229e05c(unsigned char *self)
{
    int ret;
    unsigned int flag;

    if (func_ov110_0229e7ac(self)) {
        func_ov110_0229c8f4(self);
        return;
    }
    if (func_ov002_02208054(self, 1)) {
        func_ov110_0229c8f4(self);
        return;
    }
    flag = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (flag > 0) {
        ret = func_ov002_02208b00(self + 0x2344, data_021f6c58, data_021f6c54);
        if (ret >= 0) {
            func_ov002_02209114(self + 0x2344, ret, 1);
            *(self + 0xf9) = *(self + ret + 0x2731);
            func_ov002_02208098((void *) (self), 0x12);
        }
    }
}
