/* func_ov003_022187d4 @ 0x022187d4, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
    short c;
} UnkStruct_022187d4;

typedef struct {
    unsigned char pad_00[0x7d4];
    UnkStruct_022187d4 sub;
} UnkStruct_022187d4_2;

extern void func_0200fbc4(UnkStruct_022187d4_2 *self, unsigned int a, unsigned int b, short c);

void func_ov003_022187d4(UnkStruct_022187d4_2 *self)
{
    UnkStruct_022187d4 *s;
    s = &self->sub;
    func_0200fbc4(self, s->a, s->b, s->c);
}
