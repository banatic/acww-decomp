/* func_020448b8 @ 0x020448b8, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void *self);
extern int func_0204f5e0(int p1, int p2, int p3, int p4, int p5, int p6);
extern int func_020644cc(int size);
extern void func_02044958(int value, int *data, int flag);

typedef struct {
    int a;
    int b;
} SELF;

void func_020448b8(SELF *self)
{
    int result1;
    int result2;
    int flag;
    int vals[2];
    int a;
    int b;
    int ash;
    int bsh;

    result1 = func_0204e414(self);
    if (result1 == 0) {
        return;
    }

    a = self->a;
    b = self->b;
    ash = a >> 4;
    bsh = b >> 4;
    result2 = func_0204f5e0(result1, ash, bsh, a - (ash << 4), b - (bsh << 4), 0);
    if (result2 == 0) {
        return;
    }

    flag = (func_020644cc(0x50) < 0x46) ? 1 : 0;
    vals[0] = self->a;
    vals[1] = self->b;
    func_02044958(result2, vals, flag);
}
