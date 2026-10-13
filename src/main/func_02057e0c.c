/* func_02057e0c @ 0x02057e0c, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021c9374;
extern unsigned int data_021c9368;
extern unsigned char data_021c9340[];
extern unsigned char data_020cbaf4[];
extern int _s32_div_f(unsigned int, unsigned char);
extern void func_0205967c(void *, void *);
extern void func_02059674(void *, int);
extern void func_020ea6e0(void *, short);
extern void VEC_Add(void *, void *, void *);
extern void func_020e895c(void *, unsigned int, unsigned int);

typedef struct UnkStruct_02057e0c {
    unsigned char pad_00[0x60];
    unsigned char unk_60[0x18];
    unsigned int vec78[3];
    unsigned char buf84[0xc];
    unsigned int size90;
    unsigned int size94;
    unsigned int size98;
    unsigned char pad_9C[0xc];
    unsigned int vecA8[3];
    unsigned char pad_B4[0x18];
    void *unk_CC;
    unsigned char pad_D0[4];
    unsigned char stateD4;
    unsigned char pad_D5;
    unsigned short countD6;
} UnkStruct_02057e0c;

void func_02057e0c(UnkStruct_02057e0c *self)
{
    unsigned int local;
    unsigned int tmp;
    unsigned char limit;
    int v;

    if ((data_021c9374 & 1) == 0) {
        v = _s32_div_f(0x1000, data_021c9340[1]);
        if (v < 0) {
            v = -v;
        }
        data_021c9368 = v;
        data_021c9374 |= 1;
    }

    local = self->vecA8[0];
    limit = data_020cbaf4[2];

    if (self->countD6 >= limit) {
        return;
    }

    func_0205967c(self, &self->unk_60);
    func_020e895c(&local, 0, data_021c9368);
    tmp = local;
    self->vecA8[0] = tmp;
    self->vecA8[1] = tmp;
    self->vecA8[2] = tmp;
    func_020e895c(&self->buf84[0], 0, self->size90);
    func_020e895c(&self->buf84[4], 0, self->size94);
    func_020e895c(&self->buf84[8], 0, self->size98);

    if (self->unk_CC != 0) {
        self->vec78[0] = *(unsigned int *) &self->buf84[0];
        self->vec78[1] = *(unsigned int *) &self->buf84[4];
        self->vec78[2] = *(unsigned int *) &self->buf84[8];
        func_020ea6e0(self->vec78, *(short *) ((char *) self->unk_CC + 0x8e));
    }

    VEC_Add(&self->unk_60, self->vec78, &self->unk_60);

    self->countD6++;
    if (self->countD6 < limit) {
        return;
    }

    self->stateD4 = 3;
    func_02059674(self, 0);
}