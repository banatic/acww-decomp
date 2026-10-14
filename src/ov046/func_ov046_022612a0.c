/* func_ov046_022612a0 @ 0x022612a0, 0x2c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[0xb8];
    Pair pair;
    int c0;
} UnkStruct_022612a0;

extern void func_0201612c(UnkStruct_022612a0 *self);
extern int func_020b1580(void);
extern Pair __ptmf_null;

void func_ov046_022612a0(UnkStruct_022612a0 *self)
{
    func_0201612c(self);
    self->pair = __ptmf_null;
    self->c0 = func_020b1580();
}
