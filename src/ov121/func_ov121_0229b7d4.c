/* func_ov121_0229b7d4 @ 0x0229b7d4, 0xec bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern int func_02002c6c(void *dst, void *src, int size, int a, int b, int c);
extern void *func_020e9958(void *pool, int size);
extern int func_020984e8(void);
extern void *func_020996b8(void *object);
extern void *func_02072bb0(void *p, int idx);
extern void *func_02072da0(void *object);
extern void func_020025c4(void *a, void *b, int c, int d, int e);
extern int func_02002a88(void *a, int b, int c, int d, int e);
extern void func_020e993c(void *a, void *b);
extern void *func_02072d4c(void *p);
extern void *func_02072f88(void *p);
extern void MIi_CpuCopy16(void *src, void *dst, int size);
extern int func_02064af4(const void *src, void *dst, int size);
extern int func_02002bd0(void *a, int b, int c, int d, int e);

extern unsigned char data_ov121_0229c408[];
extern unsigned char data_ov121_0229c420[];

void func_ov121_0229b7d4(void)
{
    void *pool = data_021fbe94;
    void *ptr1, *ptr2;
    void *local;
    unsigned char i;
    int off;

    func_02002c6c((void *) data_ov121_0229c408, pool, 8, 0x140, 0x140, 0x17f);
    ptr1 = func_020e9958(pool, 0x1000);
    local = func_020996b8((void *) func_020984e8());

    for (i = 0; i < 8; i++) {
        void *a = func_02072bb0(local, i);
        void *b = func_02072da0(a);
        func_020025c4(b, ptr1, i * 4, 4, 4);
    }

    func_02002a88(ptr1, 8, 0xc0, 0xc0, 0x13f);
    func_020e993c(pool, ptr1);

    ptr2 = func_020e9958(pool, 0x120);
    off = 0;
    for (i = 0; i < 8; i++) {
        void *a = func_02072bb0(local, i);
        void *b = func_02072d4c(a);
        void *c = func_02072f88(b);
        MIi_CpuCopy16(c, (char *) ptr2 + off * 2, 0x20);
        off += 0x10;
    }

    func_02064af4((const void *) data_ov121_0229c420, (char *) ptr2 + off * 2, 0x20);
    func_02002bd0(ptr2, 8, 4, 4, 0xc);
    func_020e993c(pool, ptr2);
}
