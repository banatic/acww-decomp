/* func_ov004_02246c7c @ 0x02246c7c, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02246c7c {
    short unk_00;
    short unk_02;
    int w0, w1, w2, w3, w4, w5, w6;
} UnkStruct_02246c7c;

#define S32(o) (*(int *) ((char *) self + (o)))
#define S16(o) (*(short *) ((char *) self + (o)))

extern void func_0203c97c(void *self, void *p);
extern void func_0203ad58(void);

extern unsigned char data_ov004_0225697c[];
extern unsigned char data_ov004_022569cc[];

void func_ov004_02246c7c(void *self)
{
    UnkStruct_02246c7c *g;

    g = (UnkStruct_02246c7c *) data_ov004_022569cc;
    S16(0xfc) = g->unk_00;
    S16(0xfe) = g->unk_02;
    S32(0x100) = g->w0;
    S32(0x104) = g->w1;
    S32(0x108) = g->w2;
    S32(0x10c) = g->w3;
    S32(0x110) = g->w4;
    S32(0x114) = g->w5;
    S32(0x118) = g->w6;
    func_0203c97c(self, (void *) data_ov004_0225697c);
    func_0203ad58();
}
