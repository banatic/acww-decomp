/* func_020372f8 @ 0x020372f8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da2c4;

struct F0x020372f8 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned short d;
    unsigned char e;
    unsigned char unk_0F;
    unsigned char g;
};

void func_020372f8(struct F0x020372f8 *s, unsigned int v)
{
    s->a = (unsigned int) &data_020da2c4;
    s->b = v;
    s->c = 0x18;
    s->d = 0xffff;
    s->e = 0;
    s->unk_0F = 0;
    s->g = 0;
}
