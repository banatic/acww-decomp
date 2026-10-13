/* func_ov114_0229c370 @ 0x0229c370, 0x3c bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov114_0229c690(void);
extern int _s32_div_f(int a, int b);

typedef struct {
    unsigned char pad_00[0x127c];
    int unk_127C;
    unsigned char pad_1280[0x1294 - 0x127c - 4];
    int unk_1294;
} UnkNisB;

unsigned char func_ov114_0229c370(UnkNisB *self)
{
    int ret = func_ov114_0229c690();
    ret = ret - (21 - self->unk_127C);
    if (ret < 0) {
        ret = 0;
    }
    ret = _s32_div_f(ret, 27);
    if (ret >= self->unk_1294) {
        ret = self->unk_1294 - 1;
    }
    return (unsigned char) (ret + 13);
}
