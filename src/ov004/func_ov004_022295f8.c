/* func_ov004_022295f8 @ 0x022295f8, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
    short c;
} UnkStruct_022295f8;

typedef struct {
    unsigned char pad_00[0x7d4];
    UnkStruct_022295f8 sub;
} UnkStruct_022295f8_2;

extern void func_0200fbc4(UnkStruct_022295f8_2 *self, unsigned int a, unsigned int b, short c);

void func_ov004_022295f8(UnkStruct_022295f8_2 *self)
{
    UnkStruct_022295f8 *s;
    s = &self->sub;
    func_0200fbc4(self, s->a, s->b, s->c);
}
