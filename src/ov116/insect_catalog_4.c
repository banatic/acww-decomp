/* insect_catalog_4: 9 functions, module ov116
 * mwccarm 1.2/base -O4,s
 * func_ov116_0229e34c @ 0x0229e34c, 0x8 bytes, Thumb
 * func_ov116_0229e334 @ 0x0229e334, 0x16 bytes, Thumb
 * func_ov116_0229e328 @ 0x0229e328, 0xc bytes, Thumb
 * func_ov116_0229e2e0 @ 0x0229e2e0, 0x46 bytes, Thumb
 * func_ov116_0229e2c8 @ 0x0229e2c8, 0x18 bytes, Thumb
 * func_ov116_0229e2b0 @ 0x0229e2b0, 0x18 bytes, Thumb
 * func_ov116_0229e228 @ 0x0229e228, 0x88 bytes, Thumb
 * func_ov116_0229e1f0 @ 0x0229e1f0, 0x38 bytes, Thumb
 * func_ov116_0229e168 @ 0x0229e168, 0x88 bytes, Thumb
 */

extern void func_ov114_0229d87c(void *);
extern void func_ov116_0229df50(void *);
extern void func_ov114_0229d824(void *ptr);
extern void func_020029e8(int layer, int priority);
extern void func_020028bc(unsigned int mode, int a, int b, int c);
extern void func_ov114_0229d700(void *);
extern void func_ov114_0229c8dc(void *);
extern void func_ov114_0229d688(void *receiver);
extern void func_ov114_0229cadc(void *);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02208054(char *self, int a);
extern void func_ov116_0229df8c(char *self);
extern int func_ov114_0229d564(char *p, unsigned char a, unsigned char b);
extern int func_ov114_0229d3f4(char *p, unsigned char a, unsigned char b);
extern int func_ov114_0229ca50(char *p, unsigned char a, unsigned char b);
extern unsigned char *func_ov002_02208098(char *self, unsigned char value);
extern void func_ov114_0229d32c(char *p, unsigned char b);
extern void func_ov114_0229d304(char *p);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *p);
extern int func_ov114_0229c410(void *p, int x);
extern int func_ov090_02299078(int x);
extern int func_ov090_02299098(int x);
extern void func_ov116_0229dfa8(void *p);
extern void func_ov116_0229de60(void *p);
extern void func_ov116_0229ddf8(void *p);
extern int func_ov116_0229e4cc(void *p, int x);
extern struct {
    unsigned short field0;
    unsigned short flags;
} data_021fbe40;

void func_ov116_0229e328(void *self);

void func_ov116_0229e34c(void *arg0)
{
    func_ov116_0229e328((void *) arg0);
}

void func_ov116_0229e334(void *self)
{
    func_ov114_0229d87c((char *) self + 0xf8);
    func_ov116_0229df50(self);
}

void func_ov116_0229e328(void *self)
{
    func_ov114_0229d824((char *) self + 0xf8);
}

void func_ov116_0229e2e0(void)
{
    func_020029e8(3, 1);
    func_020028bc(3, 0, 0, 0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
}

void func_ov116_0229e2c8(void *p)
{
    func_ov114_0229d700((char *) p + 0xf8);
    func_ov114_0229c8dc((char *) p + 0xf8);
}

void func_ov116_0229e2b0(void *param)
{
    void *p;
    p = (char *) param + 0xf8;
    func_ov114_0229d688(p);
    p = (char *) param + 0xf8;
    func_ov114_0229cadc(p);
}

void func_ov116_0229e228(char *self)
{
    unsigned int cond;
    unsigned char b;
    unsigned char c;
    if (func_ov002_02208054(self, 1)) {
        func_ov116_0229df8c(self);
        return;
    }
    cond = ((data_021fbdd8 != 0) && (data_021fbddc != 0)) ? (1) : (0);
    if (cond > 0) {
        if (b) {
            b = data_021f6c58;
            c = data_021f6c54;
        } else {
            b = data_021f6c58;
            c = data_021f6c54;
        }
        if (func_ov114_0229d564(self + 0xf8, b, c) == 0) {
            if (func_ov114_0229d3f4(self + 0xf8, b, c) != 0) {
                func_ov002_02208098(self, 1);
                return;
            }
            self = self + (0xf8 & 0xFFFFFFFFFFFFFFFF);
            if (func_ov114_0229ca50(self, b, c)) {
                return;
            }
        }
    }
}

void func_ov116_0229e1f0(char *arg)
{
    if (data_021fbdd8) {
        func_ov114_0229d32c(arg + 0xf8, data_021f6c58);
    } else {
        func_ov114_0229d304(arg + 0xf8);
        func_ov002_02208098(arg, 0);
    }
}

void func_ov116_0229e168(void *param)
{
    unsigned short flags;

    if (func_ov002_02208014(param)) {
        func_ov116_0229dfa8(param);
        return;
    }
    if (func_ov114_0229c410((char *) param + 0xF8, func_ov002_02208008(param))) {
        func_ov116_0229de60(param);
        return;
    }
    flags = data_021fbe40.flags;
    if (flags & 1) {
        func_ov116_0229ddf8(param);
        return;
    }
    if (flags & 0x100) {
        func_ov116_0229e4cc(param, func_ov090_02299078(3));
        return;
    }
    if (flags & 0x200) {
        func_ov116_0229e4cc(param, func_ov090_02299098(3));
    }
}
