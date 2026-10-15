/* func_ov120_0229b9dc @ 0x0229b9dc, 0x8c bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern unsigned int data_ov120_0229c780;
extern unsigned int data_ov120_0229c820;
extern unsigned int data_ov120_0229c78c;
extern void *func_ov117_0229a2f0(unsigned int *p);
extern void func_ov117_0229a2c8(unsigned int *p);
extern void func_ov117_02299a48(void *a, unsigned int *p);
extern void func_ov117_0229a2ec(void *object);
extern void func_ov120_0229af10(void *a, unsigned int *p);
extern void *func_020e9958(void *p, unsigned int n);
extern void __register_global_object(unsigned int *a, void *destructor, unsigned int *c);
extern int func_02002a88(void *a, int b, int c, int d, int e);
extern void func_020e993c(void *a, void *b);

#define DisposeGlobal_func_ov117_0229a2ec ((void *) &func_ov117_0229a2ec)

void func_ov120_0229b9dc(void *a)
{
    void *p;
    void *r;

    p = data_021fbe94;
    r = func_020e9958(p, 0x2000);
    if (!(data_ov120_0229c780 & 1)) {
        func_ov117_0229a2f0(&data_ov120_0229c820);
        __register_global_object(&data_ov120_0229c820, DisposeGlobal_func_ov117_0229a2ec, &data_ov120_0229c78c);
        data_ov120_0229c780 |= 1;
    }
    func_ov117_0229a2c8(&data_ov120_0229c820);
    func_ov117_02299a48(r, &data_ov120_0229c820);
    func_02002a88(r, 4, 0x60, 0x60, 0x15f);
    func_ov120_0229af10(a, &data_ov120_0229c820);
    func_020e993c(p, r);
}

#undef DisposeGlobal_func_ov117_0229a2ec
