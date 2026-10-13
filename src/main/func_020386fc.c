/* func_020386fc @ 0x020386fc, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020386fc {
    unsigned char pad_00[0xca];
    unsigned char unk_CA;
    unsigned char unk_CB;
    unsigned short unk_CC;
    unsigned short unk_CE;
};

#define HWREG1 (*(volatile unsigned short *) 0x04000050)
#define HWREG2 (*(volatile unsigned short *) 0x04001050)

void func_020386fc(struct UnkStruct_020386fc *p)
{
    if (p->unk_CB == 0) {
        return;
    }

    if (p->unk_CA != 0) {
        p->unk_CC = HWREG1;
        p->unk_CE = HWREG2;
        HWREG1 = 0;
        HWREG2 = 0;
    } else {
        HWREG1 = p->unk_CC;
        HWREG2 = p->unk_CE;
    }

    p->unk_CB = 0;
}
