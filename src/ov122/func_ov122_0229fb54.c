/* func_ov122_0229fb54 @ 0x0229fb54, 0xd8 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

struct UnkStruct_0229fb54 {
    unsigned char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    unsigned char pad_A4[6];
    unsigned char unk_AA;
    unsigned char pad_AB[1];
    unsigned char unk_AC;
    unsigned char pad_AD[1];
    unsigned char unk_AE;
    unsigned char pad_AF[4];
    unsigned char unk_B3;
    unsigned char pad_B4[8];
    unsigned char *unk_BC;
};

extern void func_ov122_0229fea4(struct UnkStruct_0229fb54 *p);
extern void func_ov122_0229efd8(struct UnkStruct_0229fb54 *p, int v);
extern void func_ov122_0229f590(struct UnkStruct_0229fb54 *p, int v);
extern void func_ov122_0229fa90(struct UnkStruct_0229fb54 *p);
extern void func_ov122_0229fd88(struct UnkStruct_0229fb54 *p, int v);
extern void func_ov122_0229fcfc(struct UnkStruct_0229fb54 *p);

int func_ov122_0229fb54(struct UnkStruct_0229fb54 *p)
{
    int a;
    int b;
    unsigned char old;
    unsigned char mode;

    a = data_021f6c58;
    b = data_021f6c54;
    old = p->unk_AC;
    if (a < 0x30) {
        a = 0x30;
    }
    b += p->unk_B3;
    mode = p->unk_AA;

    switch (mode) {
        case 0:
        case 1:
            p->unk_9C = a;
            func_ov122_0229fea4(p);
            if (p->unk_AA == mode) {
                break;
            }
            p->unk_AA = mode;
            func_ov122_0229efd8(p, 0x1000);
            if (mode == 0) {
                func_ov122_0229f590(p, p->unk_BC[0xf8]);
            } else {
                func_ov122_0229f590(p, 0);
            }
            func_ov122_0229fa90(p);
            break;
        case 2:
            p->unk_9C = a;
            p->unk_A0 = b;
            func_ov122_0229fd88(p, 0);
            break;
        case 3:
            p->unk_9C = a;
            func_ov122_0229fcfc(p);
            break;
    }

    p->unk_AE = p->unk_AC;
    return p->unk_AC != old ? 1 : 0;
}
