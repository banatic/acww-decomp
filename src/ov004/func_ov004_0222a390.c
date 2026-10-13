/* func_ov004_0222a390 @ 0x0222a390, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
    short c;
} UnkStruct_0222a390;

typedef struct {
    unsigned char pad_00[0x7d4];
    UnkStruct_0222a390 sub;
} UnkStruct_0222a390_2;

extern void func_0200fbc4(UnkStruct_0222a390_2 *self, unsigned int a, unsigned int b, short c);

void func_ov004_0222a390(UnkStruct_0222a390_2 *self)
{
    UnkStruct_0222a390 *s;
    s = &self->sub;
    func_0200fbc4(self, s->a, s->b, s->c);
}
