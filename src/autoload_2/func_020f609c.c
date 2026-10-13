/* func_020f609c @ 0x020f609c, 0xf8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

// Sound/sequence step. The null test is consumed by a switch, which keeps the 0/1 value.
struct UnkStruct_020f609c {
    int unk_00;
    unsigned short unk_04;
    signed char unk_06;
};
struct UnkStruct_020f609c_2 {
    int pad_00;
};
extern unsigned char *data_021fd268;
extern struct UnkStruct_020f609c_2 data_021fd1bc;
extern void func_020eed18(struct UnkStruct_020f609c *, int);
extern int func_020f1d3c(struct UnkStruct_020f609c_2 *, int);
extern void NNS_SndArcPlayerStartSeqArc(struct UnkStruct_020f609c *, unsigned short, unsigned short);
extern void func_020f5fa8(struct UnkStruct_020f609c *, int);

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
