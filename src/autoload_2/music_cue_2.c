/* music_cue_2: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f9e00 @ 0x020f9e00, 0xa4 bytes, ARM
 * func_020f9d00 @ 0x020f9d00, 0x100 bytes, ARM
 */

typedef struct {
    unsigned char pad_00[6];
    unsigned short unk_06;
    unsigned char pad_08[3];
    signed char unk_0B;
    unsigned char pad_0C;
    signed char unk_0D;
} UnkStruct_020f9e00;

extern int NNS_SndPlayerWriteVariable(void *self, int id, int value);
extern void func_020f9c0c(void *self);
extern int NNS_SndPlayerReadGlobalVariable(int index, signed short *out);
extern int NNS_SndPlayerReadVariable(void *player, int id, signed short *out);
extern signed short data_021fd26c;
extern signed short data_021fd270;
extern unsigned char data_021fd1bc[];

void func_020f9e00(UnkStruct_020f9e00 *self)
{
    int ip;
    unsigned int found;

    if (self->unk_0D == -1) {
        return;
    }
    if (self->unk_0D != self->unk_0B) {
        return;
    }

    ip = 0xf - (self->unk_0B + 1);
    found = 0;

    if (ip >= 0) {
        unsigned short v = self->unk_06;
        do {
            if ((v >> ip) & 1) {
                found = 1;
                break;
            }
            ip--;
        } while (ip >= 0);
    }

    if (!found) {
        unsigned short v = self->unk_06;
        ip = 15;
        do {
            if ((v >> ip) & 1) {
                break;
            }
            ip--;
        } while (ip >= 0);
    }

    self->unk_0D = (signed char) (0xf - ip);
    NNS_SndPlayerWriteVariable(self, 0xc, self->unk_0D);
}

void func_020f9d00(void *self)
{
    signed short vars[6];
    unsigned int val;
    unsigned int flag;

    if (((signed char *) self)[9] <= 0) {
        func_020f9c0c(self);
    }

    NNS_SndPlayerReadGlobalVariable(2, &vars[0]);
    NNS_SndPlayerReadGlobalVariable(1, &vars[1]);
    NNS_SndPlayerReadVariable(self, 8, &vars[2]);
    NNS_SndPlayerReadVariable(self, 7, &vars[3]);
    NNS_SndPlayerReadVariable(self, 12, &vars[4]);
    NNS_SndPlayerReadVariable(self, 6, &vars[5]);

    data_021fd26c = vars[0];
    data_021fd270 = vars[1];

    ((signed char *) self)[0xb] = (signed char) vars[2];
    ((signed char *) self)[0xc] = (signed char) vars[3];
    ((signed char *) self)[0xd] = (signed char) vars[4];
    ((signed char *) self)[0xe] = (signed char) vars[5];

    val = *(unsigned int *) (data_021fd1bc + 0x3c);
    flag = (val != 0) ? 1 : 0;
    if (flag == 0) {
        return;
    }

    if (*(unsigned short *) (val + 0x38) == 0xf0) {
        data_021fd270 >>= 1;
    }
}
