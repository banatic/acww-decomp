/* func_02077690 @ 0x02077690, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    unsigned short h;
    unsigned char b[3];
} UnkStruct_02077690;

extern void *data_020ccf94;
extern void (*data_020ccf98[])(void *);

extern void func_02073044(void);
extern int func_020ebf70(void);
extern void func_02073320(void *g);
extern unsigned char *func_02073d28(void *g, int k);
extern void func_02077b3c(unsigned char *p, int a, int b);
extern void func_02073338(void *g, unsigned int n);
extern unsigned int func_0207332c(void *g);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);

int func_02077690(void *a)
{
    void *g;
    int i;
    unsigned int pos;
    unsigned char *dst;
    unsigned int cur;
    UnkStruct_02077690 t;

    func_02073044();
    if (func_020ebf70() == 0) {
        return 0;
    }
    g = data_020ccf94;
    func_02073320(g);
    func_02077b3c(func_02073d28(g, 4), 0, 0xd);
    func_02073338(g, 1);
    for (i = 0; i < 2; i++) {
        pos = func_0207332c(g);
        dst = func_02073d28(g, 4) + pos;
        func_02073338(g, pos + 3);
        data_020ccf98[i](a);
        cur = func_0207332c(g);
        if (cur <= pos + 3) {
            func_02073338(g, pos);
        } else {
            t.h = (unsigned short) (cur - pos - 3);
            MI_CpuCopy8(&t.h, t.b, 2);
            t.b[2] = (unsigned char) i;
            MI_CpuCopy8(t.b, dst, 3);
        }
    }
    return 1;
}
