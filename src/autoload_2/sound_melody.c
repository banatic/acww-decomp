/* sound_melody: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f609c @ 0x020f609c, 0xf8 bytes, ARM
 * func_020f6000 @ 0x020f6000, 0x9c bytes, ARM
 */

struct UnkStruct_020f609c {
    int unk_00;
    unsigned short unk_04;
    signed char unk_06;
};

struct UnkStruct_020f609c_2 {
    int pad_00;
};

struct UnkStruct_020f6000 {
    char pad_00[0x3c];
    char unk_3C;
};

struct UnkStruct_020f6000_2 {
    char pad_00[0x30];
    struct UnkStruct_020f6000 *ptr;
};

struct Unknown_s {
    char pad_00[6];
    signed char unk_06;
    char unk_07;
    char pad_08;
    signed char unk_09;
    char unk_0A;
};

extern unsigned char *data_021fd268;
extern struct UnkStruct_020f609c_2 data_021fd1bc;
extern int func_020eed18(struct UnkStruct_020f609c *, int);
extern int func_020f1d3c(struct UnkStruct_020f609c_2 *, int);
extern int NNS_SndArcPlayerStartSeqArc(struct UnkStruct_020f609c *, unsigned short, unsigned short);
extern void func_020f5fa8(struct UnkStruct_020f609c *, int);

// Sound/sequence step. The null test is consumed by a switch, which keeps the 0/1 value.
void func_020f609c(struct UnkStruct_020f609c *self, int a1)
{
    unsigned char b = data_021fd268[self->unk_06];
    int flag;
    switch (b) {
        case 13:
            flag = (self->unk_00 != 0);
            switch (flag) {
                case 0:
                    break;
                default:
                    func_020eed18(self, 0);
                    break;
            }
            NNS_SndArcPlayerStartSeqArc(self, self->unk_04, (unsigned short) (b + 1 + func_020f1d3c(&data_021fd1bc, 6)));
            func_020f5fa8(self, a1);
            break;
        case 14:
        case 15:
            break;
        default:
            flag = (self->unk_00 != 0);
            switch (flag) {
                case 0:
                    break;
                default:
                    func_020eed18(self, 0);
                    break;
            }
            NNS_SndArcPlayerStartSeqArc(self, self->unk_04, (unsigned short) (b + 1));
            func_020f5fa8(self, a1);
            break;
    }
}

int func_020f6000(struct Unknown_s *self)
{
    if (self->unk_06 >= 15) {
        func_020eed18((struct UnkStruct_020f609c *) self, 0);
        (*(struct UnkStruct_020f6000_2 *) &data_021fd1bc).ptr->unk_3C = 0;
        self->unk_0A = 0;
        self->unk_06 = -1;
        self->unk_07 = 0;
        return 1;
    }

    {
        int idx = self->unk_06 + 1;
        unsigned char b = data_021fd268[idx];

        if (b != 14) {
            if (b == 15) {
                if (self->unk_09 != 1) {
                    func_020eed18((struct UnkStruct_020f609c *) self, 0);
                }
            } else {
                func_020eed18((struct UnkStruct_020f609c *) self, 0);
            }
        }
    }

    return 0;
}
