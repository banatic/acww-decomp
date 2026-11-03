/* field_actor_states_24: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200c8d8 @ 0x0200c8d8, 0x2c bytes, Thumb
 * func_0200c8c0 @ 0x0200c8c0, 0x16 bytes, Thumb
 * func_0200c89c @ 0x0200c89c, 0x22 bytes, Thumb
 */

typedef struct {
    short unk_00;
    int unk_04;
    int unk_08;
    char unk_0C;
    short unk_0E;
} Struct0200c8d8;

extern void func_020778b0(void);
extern unsigned short func_02077898(void *);

void func_0200c8d8(Struct0200c8d8 *s, short a, int b, int c, short d)
{
    s->unk_00 = a;
    s->unk_04 = b;
    s->unk_08 = c;
    s->unk_0C = 0;
    s->unk_0E = (short) (-d / 3);
}

void func_0200c8c0(unsigned char *r0, int r1, unsigned char r2, unsigned char r3)
{
    unsigned char *r5 = r0;
    unsigned char r4 = r2;
    unsigned char r6 = r3;

    func_020778b0();
    r5[2] = r4;
    r5[3] = r6;
}

void func_0200c89c(void *a, unsigned short *b, unsigned char *c, unsigned char *d)
{
    unsigned short x;
    unsigned char y, z;

    x = func_02077898(a);
    *b = x;
    y = ((unsigned char *) a)[2];
    *c = y;
    z = ((unsigned char *) a)[3];
    *d = z;
}
