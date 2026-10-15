/* func_ov050_02261174 @ 0x02261174, 0x8c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02261174 {
    char pad_00[0xb4];
    unsigned char *base;
    char pad_B8[0xc];
    int other;
    char pad_C8[0x8];
    int value;
};

extern int func_0201b43c(unsigned char *a, int b);
extern void func_0201b420(unsigned char *a, int b);
extern int func_020984e8(void);
extern int func_02099870(int argument0);
extern int func_0209871c(void *a, int b);
extern int func_020b65c4(void);
extern void func_020ada48(int a, int b, int c, int d);

extern unsigned char data_021dc7bc[];

void func_ov050_02261174(struct UnkStruct_02261174 *self, int cond)
{
    if (cond == 0) {
        if (func_0201b43c(self->base, self->other) == 0) {
            self->value = 0x21;
        } else {
            int v, rv;
            unsigned char *base;
            self->value = 0x22;
            self->base[0x73c] = 1;
            func_0201b420(self->base, self->other);

            v = func_02099870((int) func_020984e8());
            func_0209871c((void *) data_021dc7bc, v);
            base = self->base;
            rv = func_020b65c4();
            func_020ada48(*(int *) (base + 0x734), *(int *) (base + 0x738), self->other, rv);
        }
    }
}
