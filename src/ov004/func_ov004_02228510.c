/* func_ov004_02228510 @ 0x02228510, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
    short c;
} UnkStruct_02228510;

typedef struct {
    unsigned char pad_00[0x7d4];
    UnkStruct_02228510 sub;
} UnkStruct_02228510_2;

extern void func_0200fbc4(UnkStruct_02228510_2 *self, unsigned int a, unsigned int b, short c);

void func_ov004_02228510(UnkStruct_02228510_2 *self)
{
    UnkStruct_02228510 *s;
    s = &self->sub;
    func_0200fbc4(self, s->a, s->b, s->c);
}
