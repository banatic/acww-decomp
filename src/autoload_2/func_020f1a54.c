/* func_020f1a54 @ 0x020f1a54, 0x150 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void func_020f0ddc(void *something, int param);
extern void func_020f0d98(void *something, int param1, int param2);
extern void NNS_SndPlayerSetTrackVolume(void *something, unsigned int vol, int param);

struct UnkStruct_020f1a54 {
    unsigned int pad_00;
    unsigned char something[4];
    unsigned char pad_08[92];
    unsigned short unk_64;
};

void func_020f1a54(struct UnkStruct_020f1a54 *self, int idx)
{
    func_020f0ddc(&self->something[0], 0x7f);

    switch (idx) {
        case 1:
            self->unk_64 = 0x84;
            break;
        case 2:
            self->unk_64 = 0x18;
            break;
        case 3:
            self->unk_64 = 0x1800;
            break;
        case 4:
            self->unk_64 = 0x700;
            break;
        case 5:
            self->unk_64 = 0x63;
            break;
        case 6:
            self->unk_64 = 0xff18;
            break;
        case 11:
            self->unk_64 = 0xff9c;
            break;
        case 12:
            self->unk_64 = 0xff84;
            break;
        case 13:
            self->unk_64 = 0xe79c;
            break;
        case 14:
            self->unk_64 = 0xf89c;
            break;
        case 15:
            self->unk_64 = 0xf8ff;
            break;
        default:
            return;
    }

    if (idx >= 6) {
        NNS_SndPlayerSetTrackVolume((char *) self + 0x3c, self->unk_64, 0);
    } else {
        func_020f0d98(&self->something[0], 0, 0xf);
    }
}
