/* func_ov004_02246de8 @ 0x02246de8, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02246de8 {
    short unk_00, unk_02, unk_04, unk_06, unk_08, unk_0A, unk_0C;
    unsigned char unk_0E;
} UnkStruct_02246de8;

typedef struct UnkStruct_02246de8_2 {
    short unk_00;
    short unk_02;
    int w0, w1, w2, w3, w4, w5, w6;
} UnkStruct_02246de8_2;

#define S32(o) (*(int *) ((char *) self + (o)))
#define S16(o) (*(short *) ((char *) self + (o)))

extern void func_0203c97c(void *self, void *p);
extern void func_0203ad58(void);

extern unsigned char data_ov004_0225696c[];
extern unsigned char data_ov004_022569ac[];

int func_ov004_02246de8(void *self)
{
    UnkStruct_02246de8 *b;
    UnkStruct_02246de8_2 *g;

    b = (UnkStruct_02246de8 *) ((char *) self + 0x21c);
    b->unk_00 = 0;
    b->unk_02 = -1;
    b->unk_04 = 0;
    b->unk_06 = -1;
    b->unk_08 = -1;
    b->unk_0A = 0;
    b->unk_0C = 0xe;
    b->unk_0E &= ~1;
    b->unk_0E &= ~2;
    g = (UnkStruct_02246de8_2 *) data_ov004_022569ac;
    S16(0xfc) = g->unk_00;
    S16(0xfe) = g->unk_02;
    S32(0x100) = g->w0;
    S32(0x104) = g->w1;
    S32(0x108) = g->w2;
    S32(0x10c) = g->w3;
    S32(0x110) = g->w4;
    S32(0x114) = g->w5;
    S32(0x118) = g->w6;
    func_0203c97c(self, (void *) data_ov004_0225696c);
    func_0203ad58();
    return 1;
}
