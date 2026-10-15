/* func_ov123_0229baa4 @ 0x0229baa4, 0xd0 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xaa];
    unsigned char unk_AA;
    unsigned char unk_AB;
    unsigned char unk_AC;
} ThisType;

typedef struct {
    unsigned char pad_00[2];
    unsigned short u16_at_2;
} UnkStruct_0229baa4;

extern UnkStruct_0229baa4 data_021fbe40;

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *);
extern void func_ov123_0229b6d0(void *);
extern int func_ov123_022999b0(void *, int, int);
extern void func_ov123_0229a438(void *);
extern void func_ov123_02299640(void *, unsigned int);
extern void func_ov123_0229a340(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void RtcSendPxiCommand(unsigned int);
extern void func_ov123_0229b65c(void *);
extern int func_ov123_022998c0(void *);
extern void func_ov123_02299980(void *);
extern void func_ov123_02299d00(void *);
extern void func_ov123_0229b5cc(void *);

void func_ov123_0229baa4(ThisType *this)
{
    unsigned short flags;

    if (func_ov002_02208014(this) != 0) {
        func_ov123_0229b6d0(this);
        return;
    }

    func_ov123_022999b0(this, func_ov002_02208008(this), 0);

    flags = data_021fbe40.u16_at_2;
    if (flags & 0x1) {
        func_ov123_0229a438(this);
        return;
    }
    if (flags & 0x2) {
        func_ov123_02299640(this, 0x800);
        func_ov123_0229a340(this);
        func_ov002_02208098(this, 7);
        return;
    }
    if (flags & 0x800) {
        RtcSendPxiCommand(0x864);
        this->unk_AC = 0;
        this->unk_AA = this->unk_AB;
        func_ov123_0229b65c(this);
        return;
    }

    if (func_ov123_022998c0(this)) {
        return;
    }

    flags = data_021fbe40.u16_at_2;
    if (flags & 0x400) {
        func_ov123_02299980(this);
        return;
    }
    if (flags & 0x8) {
        func_ov123_02299d00(this);
        func_ov123_0229b5cc(this);
    }
}
