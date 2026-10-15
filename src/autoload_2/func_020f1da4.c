/* func_020f1da4 @ 0x020f1da4, 0x128 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

// Sound parameter setup using the soft-float helpers.
#pragma opt_propagation off
typedef struct {
    char pad_00[0x44];
    int type;
    int unk_48;
} UnkStruct_020f1da4;

extern double _dfltu(int a);
extern double _dmul(double a, double b);
extern int func_0213460c(double a);

extern int func_020eedb8(unsigned short rem, unsigned short quot, void *p);
extern void NNS_SndPlayerSetVolume(void *p, int a);
extern void NNS_SndPlayerSetTrackPitch(void *p, int a, int b);

void func_020f1da4(UnkStruct_020f1da4 *self, int p1, int p2, int p3)
{
    int flag;

    switch (self->type) {
        case 3:
            p3 -= 400;
            p2 = func_0213460c(_dmul(_dfltu(p2), 1.38)) & 0xff;
            if ((unsigned int) p2 > 0x7f) {
                p2 = 0x7f;
            }
            break;
        case 4:
            p3 += 600;
            p2 = func_0213460c(_dmul(_dfltu(p2), 1.23)) & 0xff;
            if ((unsigned int) p2 > 0x7f) {
                p2 = 0x7f;
            }
            break;
    }

    func_020eedb8((unsigned short) (p1 % 1000), (unsigned short) (p1 / 1000), (char *) self + 0x48);

    flag = (self->unk_48 != 0);
    if (flag != 0) {
        NNS_SndPlayerSetVolume((char *) self + 0x48, p2);
        NNS_SndPlayerSetTrackPitch((char *) self + 0x48, 15, p3);
    }
}
