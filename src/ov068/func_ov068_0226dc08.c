/* func_ov068_0226dc08 @ 0x0226dc08, 0x5c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int x);

typedef struct {
    unsigned char pad[0x21e];
    unsigned short v1;
    unsigned char pad_220[2];
    unsigned short v2;
    unsigned char pad_224;
    unsigned char idx;
} UnkStruct_0226dc08;

typedef struct {
    unsigned short w;
    unsigned char pad[10];
} TabEntry;

extern TabEntry data_020ca17c[];
extern TabEntry data_020ca17e[];

void func_ov068_0226dc08(UnkStruct_0226dc08 *self, unsigned char arg)
{
    self->idx = arg;
    if (self->idx >= 4) {
        self->idx = 0;
    }

    self->v2 = data_020ca17c[self->idx].w;
    self->v2 = (unsigned short) (self->v2 + func_020644cc(data_020ca17e[self->idx].w));
    self->v1 = 0;
}
