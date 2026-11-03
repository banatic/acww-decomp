/* pockets_town: 10 functions, module ov098
 * mwccarm 1.2/base -O4,s
 * func_ov098_022a29d0 @ 0x022a29d0, 0x3c bytes, Thumb
 * func_ov098_022a29b0 @ 0x022a29b0, 0x1e bytes, Thumb
 * func_ov098_022a2994 @ 0x022a2994, 0x1c bytes, Thumb
 * func_ov098_022a28ec @ 0x022a28ec, 0xa8 bytes, Thumb
 * func_ov098_022a28d0 @ 0x022a28d0, 0x1c bytes, Thumb
 * func_ov098_022a28ac @ 0x022a28ac, 0x24 bytes, Thumb
 * func_ov098_022a2884 @ 0x022a2884, 0x28 bytes, Thumb
 * func_ov098_022a2818 @ 0x022a2818, 0x6c bytes, Thumb
 * func_ov098_022a27f0 @ 0x022a27f0, 0x28 bytes, Thumb
 * func_ov098_022a27c0 @ 0x022a27c0, 0x30 bytes, Thumb
 */

struct UnkStruct_022a28ec {
    unsigned char pad_00[0xb6];
    unsigned char unk_B6;
};

struct UnkStruct_022a28ec_2 {
    unsigned char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_022a27c0 {
    char pad_00[0x2958];
    char arr[1];
};

extern int func_ov003_02219840(void);
extern unsigned char func_ov096_0229cbbc(void *self);
extern void func_ov003_0222c3a8(void *ptr, int x);
extern void func_ov096_0229f57c(void *p, unsigned char b);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_ov003_0222c364(int);
extern void func_ov096_0229fb9c(int);
extern void *data_020ccf94;
extern void *data_021c9b28;
extern unsigned char data_021ee418[];
extern void func_ov098_022a2ec0(struct UnkStruct_022a28ec *obj, int a, int b);
extern void *func_ov096_0229f054(struct UnkStruct_022a28ec *obj, int n);
extern int func_02073d90(void *);
extern void *func_020e9958(void *heap, unsigned int size);
extern void func_020e993c(void *heap, void *p);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
extern void *func_020900f0(void *p);
extern int func_02066830(void *a, void *b);
extern void func_02090100(void *p);
extern void func_02090140(void *p, int n);
extern void func_ov096_0229c414(int);
extern void func_ov096_0229ddd8(int);
extern unsigned short func_ov096_0229f0dc(void *a, unsigned char b);
extern int func_ov003_02219750(int v);
extern int func_ov003_02219c80(void);
extern int func_ov002_0220b764(int);
extern int func_0206f56c(void);
extern int func_ov002_0220b740(char *p);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned short data_021fbe40[];
extern void func_ov002_0220b74c(void *p);
extern int func_ov003_02219718(void);
extern void func_ov002_0220b738(void *self);
extern int func_020960f8(int, int);

void func_ov098_022a28ec(struct UnkStruct_022a28ec *obj);

void func_ov098_022a29d0(void *p)
{
    int x;

    func_ov098_022a28ec((struct UnkStruct_022a28ec *) p);
    func_ov003_02219840();
    x = func_ov096_0229cbbc(p);
    func_ov003_0222c3a8((char *) p + 0x2e14, x);
    func_ov096_0229f57c(p, *((unsigned char *) ((char *) p + 0xb6)));
    func_ov002_02208098(p, 0x33);
}

void func_ov098_022a29b0(int param)
{
    int result;

    result = func_ov003_0222c364((int) func_ov096_0229cbbc((void *) param));
    if (result == 1) {
        func_ov002_02208098((void *) param, 0x34);
    }
}

void func_ov098_022a2994(int param)
{
    int result;

    result = func_ov003_0222c364((int) func_ov096_0229cbbc((void *) param));
    if (result == 0) {
        func_ov096_0229fb9c(param);
    }
}

void func_ov098_022a28ec(struct UnkStruct_022a28ec *obj)
{
    struct UnkStruct_022a28ec_2 *ctx;
    void *heap;
    unsigned char *buf;
    void *src;
    void *ptr;
    void *w;

    func_ov098_022a2ec0(obj, 0, 5);
    src = func_ov096_0229f054(obj, obj->unk_B6);
    ctx = (struct UnkStruct_022a28ec_2 *) data_020ccf94;
    if (func_02073d90(ctx) == 0 || ctx->unk_64 == 0) {
        w = data_021ee418;
        func_02066830(func_020900f0(w), src);
        func_02090100(w);
        func_02090140(w, 0);
    } else {
        heap = data_021c9b28;
        buf = (unsigned char *) func_020e9958(heap, 0x101);
        buf[0] = 6;
        MI_CpuCopy8(src, buf + 1, 0x100);
        ptr = data_020ccf94;
        func_02073820(ptr);
        func_020737f0(ptr, buf, 0x101);
        func_02073770(ptr, 0x16, 0);
        func_020e993c(heap, buf);
    }
}

void func_ov098_022a28d0(int arg)
{
    func_ov002_02208098((void *) arg, 0x35);
    func_ov096_0229c414(arg);
    func_ov096_0229ddd8(arg);
}

void func_ov098_022a28ac(void *a)
{
    if (func_ov003_02219750(func_ov096_0229f0dc(a, *(unsigned char *) ((char *) a + 0xb6))) != 0) {
        func_ov002_02208098(a, 0x36);
    }
}

void func_ov098_022a2884(int r0)
{
    int r4 = r0;
    if (func_ov003_02219c80() != 0) {
        func_ov002_02208098((void *) r4, 0x37);
        func_ov002_0220b764(r4 + 0x2958);
    }
}

void func_ov098_022a2818(char *self)
{
    unsigned int b;
    func_ov002_0220b74c((void *) (self + 0x2958));
    if (func_0206f56c() != 0) {
        goto call;
    }
    b = (data_021fbdd8 && data_021fbddc);
    if (b != 0) {
        goto call;
    }
    if (data_021fbe40[1] & 1) {
        goto call;
    }
    if (data_021fbe40[1] & 2) {
        goto call;
    }
    return;
call:
    func_ov002_02208098((void *) self, 0x38);
    func_ov002_0220b740(self + 0x2958);
}

void func_ov098_022a27f0(void *arg)
{
    func_ov002_0220b74c((char *) arg + 0x2958);
    if (func_ov003_02219718()) {
        func_ov002_02208098(arg, 0x39);
    }
}

void func_ov098_022a27c0(struct UnkStruct_022a27c0 *arg)
{
    func_ov002_0220b74c((void *) &arg->arr);
    if (func_020960f8(6, 4) == 0) {
        func_ov002_0220b738((void *) arg->arr);
        func_ov096_0229fb9c((int) ((void *) arg));
    }
}
