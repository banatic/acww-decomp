/* func_ov004_02224f98 @ 0x02224f98, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02224f98 {
    unsigned char b;
    unsigned char pad_01;
    unsigned short h;
};

extern int func_0206fc6c(void);
extern unsigned int func_0206fc8c(void);
extern unsigned short *func_0206faf0(void);
extern void func_02015de4(void *self, unsigned short *p, int a, int b);
extern void func_0206844c(void *ctx, struct UnkStruct_02224f98 *t, int a);
extern int data_ov004_02254794;

void func_ov004_02224f98(char *self)
{
    struct UnkStruct_02224f98 t;
    void *ctx = *(void **) (self + 0x40);

    t.b = 0x20;
    if (func_0206fc6c() != 0) {
        if (func_0206fc8c() > 1) {
            t.b = 0x1c;
        } else {
            t.h = *func_0206faf0();
            func_02015de4(self, &t.h, 0, 7);
            t.b = 0x1e;
        }
    }
    func_0206844c(ctx, &t, data_ov004_02254794);
}
