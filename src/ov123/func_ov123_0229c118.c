/* func_ov123_0229c118 @ 0x0229c118, 0x5c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int a);
extern void func_ov002_02207eb4(void *p, int a, int b);
extern int func_ov002_0220acc4(void *p);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov123_0229c044(void *p);

struct GameObj {
    unsigned char pad_00[0x98];
    int counter;
};

void func_ov123_0229c118(struct GameObj *self)
{
    if (func_ov002_02207f3c(self, -1)) {
        func_ov002_02207eb4(self, 0, 0);
        func_ov002_0220acc4((char *) self + 0x5030);
        func_ov002_02208090(self, 0xb);
    }
    if (self->counter >= 2) {
        self->counter = self->counter - 2;
    } else {
        self->counter = 0;
    }
    func_ov123_0229c044(self);
}
