/* func_0200c8d8 @ 0x0200c8d8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short unk_00;
    int unk_04;
    int unk_08;
    char unk_0C;
    short unk_0E;
} Struct0200c8d8;

void func_0200c8d8(Struct0200c8d8 *s, short a, int b, int c, short d)
{
    s->unk_00 = a;
    s->unk_04 = b;
    s->unk_08 = c;
    s->unk_0C = 0;
    s->unk_0E = (short) (-d / 3);
}
