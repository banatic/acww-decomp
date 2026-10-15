/* func_020576cc @ 0x020576cc, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020578ec(void *);
extern void func_02057768(void *);

extern unsigned int data_020dd184;
extern unsigned int data_020dd194;

struct UnkStruct_020576cc {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    char pad_14[4];
    char sub18[0x38];
    unsigned int unk_50;
    char sub54[0x11];
    char sub65[0x13];
    unsigned int unk_78;
    unsigned int unk_7C;
    int unk_80;
    int unk_84;
    int unk_88;
};

struct UnkStruct_020576cc *func_020576cc(struct UnkStruct_020576cc *s)
{
    s->unk_00 = (unsigned int) &data_020dd184;
    s->unk_08 = 0;
    s->unk_0C = 0;
    s->unk_10 = 0x1000;
    s->unk_00 = (unsigned int) &data_020dd194;
    func_020578ec(&s->sub18);
    func_02057768(s->sub54);
    func_02057768(s->sub65);
    s->unk_50 = 0;
    s->unk_78 = 0;
    s->unk_7C = 0;
    s->unk_80 = -1;
    s->unk_84 = -1;
    s->unk_88 = -1;
    return s;
}
