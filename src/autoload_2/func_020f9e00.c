/* func_020f9e00 @ 0x020f9e00, 0xa4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void NNS_SndPlayerWriteVariable(void *self, int id, int value);

typedef struct {
    unsigned char pad_00[6];
    unsigned short unk_06;
    unsigned char pad_08[3];
    signed char unk_0B;
    unsigned char pad_0C;
    signed char unk_0D;
} UnkStruct_020f9e00;

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
