/* func_020f165c @ 0x020f165c, 0x364 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void func_020f0d98(void *h, int a, int b);
extern void NNS_SndPlayerSetTrackVolume(void *h, int track, int vol);
extern unsigned short data_0213e8d0[][4];

typedef struct {
    unsigned char pad_00[4];
    signed char unk_04;
} Kind;

typedef struct {
    unsigned char pad_00[0x38];
    unsigned short unk_38;
} Player;

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04[2];
    unsigned short unk_06;
    unsigned char pad_08[0x2c - 8];
    Kind *unk_2C;
    unsigned char pad_30[0x3c - 0x30];
    Player *unk_3C;
    unsigned char pad_40[0x64 - 0x40];
    unsigned short unk_64;
    unsigned char pad_66[0x6c - 0x66];
    short unk_6C;
    unsigned short unk_6E;
    unsigned char pad_70[0x73 - 0x70];
    unsigned char unk_73;
    unsigned char unk_74;
    unsigned char unk_75;
} UnkStruct_020f165c;

void func_020f165c(UnkStruct_020f165c *p, int mode)
{
    unsigned int idx;
    unsigned short *e;
    unsigned short mask;
    int flag;

    if (p->unk_73 != mode) {
        p->unk_75 = 1;
        switch (p->unk_73) {
            case 0:
                p->unk_74 = (unsigned char) mode;
                if (p->unk_6C > 0 || p->unk_06 != 0) {
                    p->unk_75 = 0;
                }
                break;
            case 0xb:
                switch (mode) {
                    case 0xd:
                        p->unk_74 = 3;
                        break;
                    case 0xc:
                        p->unk_74 = 1;
                        break;
                }
                break;
            case 0xc:
                p->unk_74 = 2;
                break;
            case 0xd:
                p->unk_74 = 4;
                break;
        }
        p->unk_73 = (unsigned char) mode;
    }
    if (p->unk_75 == 0) {
        return;
    }
    if (p->unk_2C == 0) {
        return;
    }
    if (p->unk_2C->unk_04 != 1 && p->unk_2C->unk_04 != 3 && p->unk_2C->unk_04 != 0x3c) {
        return;
    }
    if (!(((unsigned int) (p->unk_3C != 0)) > 0)) {
        return;
    }
    idx = (unsigned short) (p->unk_3C->unk_38 - 0x16);
    if (idx > 0x17) {
        return;
    }
    p->unk_6C = -1;
    func_020f0d98(&p->unk_04, 0, 0);
    e = data_0213e8d0[idx];
    if (e[0] == 0 && e[1] == 0 && e[2] == 0 && e[3] == 0) {
        return;
    }

    mask = 0xff;
    flag = 0;
    switch (p->unk_74) {
        case 0:
            break;
        case 1:
            mask = (unsigned short) (e[0] | e[1]);
            p->unk_6C = 200;
            p->unk_64 = e[2];
            p->unk_6E = e[1];
            p->unk_74 = 0xc;
            flag = 1;
            break;
        case 2:
            mask = (unsigned short) (e[0] | e[2]);
            p->unk_6C = 200;
            p->unk_64 = e[1];
            p->unk_6E = e[2];
            p->unk_74 = 0xb;
            flag = 1;
            break;
        case 3:
            mask = (unsigned short) (e[0] | e[1]);
            p->unk_6C = 200;
            p->unk_64 = e[3];
            p->unk_6E = e[1];
            p->unk_74 = 0xd;
            flag = 1;
            break;
        case 4:
            mask = (unsigned short) (e[0] | e[3]);
            p->unk_6C = 200;
            p->unk_64 = e[1];
            p->unk_6E = e[3];
            p->unk_74 = 0xb;
            flag = 1;
            break;
        case 11:
            mask = (unsigned short) (e[0] | e[1]);
            p->unk_64 = mask;
            flag = 1;
            break;
        case 12:
            mask = (unsigned short) (e[0] | e[2]);
            p->unk_64 = mask;
            flag = 1;
            break;
        case 13:
            mask = (unsigned short) (e[0] | e[3]);
            p->unk_64 = mask;
            flag = 1;
            break;
    }
    if (flag != 0) {
        NNS_SndPlayerSetTrackVolume(&p->unk_3C, (unsigned short) ~mask, 0);
        p->unk_75 = 0;
    }
}
