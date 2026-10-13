/* func_ov107_0229c414 @ 0x0229c414, 0x74 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
    int unk_68;
} Global;

extern Global *data_020ccf94;

extern int func_ov107_0229d0f0(void *self, unsigned char byte);
extern int func_02043d34(int a, int b, int c, int d);
extern int func_ov107_0229d480(void *self);
extern int func_ov107_0229d3a0(void *self, int a, int b);
extern unsigned short *func_02045b5c(int a);
extern int func_ov002_02208098(void *self, int a);

typedef struct {
    char pad_00[0xac];
    int unk_AC;
    char pad_B0[0xb9 - 0xac - 4];
    unsigned char unk_B9;
    char pad_BA[0xcc - 0xba];
    int unk_CC;
    int unk_D0;
} UnkStruct_0229c414;

int func_ov107_0229c414(UnkStruct_0229c414 *self)
{
    int idx = func_ov107_0229d0f0(self, self->unk_B9);
    Global *g = data_020ccf94;

    self->unk_AC = func_02043d34(g->unk_64, 2, 0, idx);

    if (self->unk_AC == -1) {
        func_ov107_0229d480(self);
        return func_ov107_0229d3a0(self, 3, 0xff);
    }

    {
        unsigned short *p = func_02045b5c(g->unk_68);
        unsigned short v = *p;
        self->unk_CC = v >> 8;
        self->unk_D0 = v & 0xff;
        return func_ov002_02208098(self, 0x16);
    }
}
