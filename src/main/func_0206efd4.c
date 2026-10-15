/* func_0206efd4 @ 0x0206efd4, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021cfc10;
extern void *data_021fbe94;
extern const char data_020df2d8[];

extern int func_020984e8(void);
extern void *func_020993a8(unsigned int);
extern int func_0203d064(void *a, void *b, int c);
extern void *func_0203cfd0(void *p);
extern void func_0206eb1c(void *a, void *b);
extern int func_02002bd0(void *a, void *b, int c, int d, int e);
extern void *func_0203cfe4(void *p);
extern void func_0200268c(void *a, void *b, int c, int d);
extern int func_02002a88(void *a, void *b, int c, int d, int e);
extern int func_02002ca4(const char *a, void *b, void *c);
extern void *func_020e9958(void *heap, int size);
extern void func_020e993c(void *heap, void *ptr);
extern int func_0206f0d4(void *p);

int func_0206efd4(void *param0)
{
    int result;
    void *heap;
    int val5;
    void *p0;
    unsigned short h;
    void *p6;
    void *p7;
    void *p2;
    void *tmp1;
    void *tmp2;

    if (data_021cfc10 != 4) {
        return func_0206f0d4(param0);
    }
    heap = data_021fbe94;
    val5 = func_020984e8();
    p0 = func_020993a8(val5);
    h = *(unsigned short *) p0;
    p6 = func_020e9958(heap, 0x200);
    if (p6 == 0) {
        return 0;
    }
    p7 = func_020e9958(heap, 0x20);
    if (p7 == 0) {
        func_020e993c(heap, p6);
        return 0;
    }
    p2 = func_020e9958(heap, 0x2c4);
    if (p2 == 0) {
        func_020e993c(heap, p6);
        func_020e993c(heap, p7);
        return 0;
    }
    func_0203d064(p2, &h, val5);
    tmp1 = func_0203cfd0(p2);
    func_0206eb1c(tmp1, p7);
    result = func_02002bd0(p7, param0, 0, 0, 0);
    tmp2 = func_0203cfe4(p2);
    func_0200268c(tmp2, p6, 4, 4);
    result &= func_02002a88(p6, param0, 0, 0, 0xf);
    func_020e993c(heap, p6);
    func_020e993c(heap, p7);
    func_020e993c(heap, p2);
    result &= func_02002ca4(data_020df2d8, heap, param0);
    return result;
}
