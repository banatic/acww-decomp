/* func_ov098_022a28ec @ 0x022a28ec, 0xa8 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void *data_021c9b28;
extern unsigned char data_021ee418[];

struct UnkStruct_022a28ec {
    unsigned char pad_00[0xb6];
    unsigned char unk_B6;
};
struct UnkStruct_022a28ec_2 {
    unsigned char pad_00[0x64];
    int unk_64;
};

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
extern void func_02066830(void *a, void *b);
extern void func_02090100(void *p);
extern void func_02090140(void *p, int n);

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
