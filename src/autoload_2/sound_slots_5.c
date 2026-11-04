/* sound_slots_5: 5 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020efbb8 @ 0x020efbb8, 0x58 bytes, ARM
 * func_020efb64 @ 0x020efb64, 0x54 bytes, ARM
 * func_020efb54 @ 0x020efb54, 0x10 bytes, ARM
 * func_020efb44 @ 0x020efb44, 0x10 bytes, ARM
 * func_020efb34 @ 0x020efb34, 0x10 bytes, ARM
 */

struct UnkStruct_020efb64_2 {
    int unk_00;
    short unk_04;
    char pad_06[4];
    unsigned char unk_0A;
    char pad_0B;
};

struct UnkStruct_020efb64 {
    char pad_00[8];
    struct UnkStruct_020efb64_2 arr[1];
    char pad_14[34];
    unsigned char flag;
};

extern void OS_Terminate(void);
extern int NNS_SndArcPlayerStartSeqArcEx(int p0, int p1, int p2, int p3, int p4, int p5);
extern unsigned short data_0213e858;
extern void NNS_SndPlayerSetTrackVolume(struct UnkStruct_020efb64_2 *e, unsigned short val, unsigned char b);
extern void NNS_SndPlayerSetTrackPitch(struct UnkStruct_020efb64_2 *e, unsigned short val, short s);
extern int data_021fd1a0;
extern unsigned int data_021fd19c;
extern int data_021fd1a4;

void func_020efbb8(int r0, int r1, int r2)
{
    int r4;
    int r5;
    int r3;
    int ip;
    int r0b;
    int r2b;
    int ipb;

    r4 = r0 + 8 + r1 * 12;
    r5 = r2;
    r0b = *(unsigned char *) (r0 + 0x36);
    if (r0b == 0) {
        OS_Terminate();
    }
    r2b = *(unsigned char *) (r4 + 8);
    r3 = -1;
    ipb = *(unsigned short *) (r4 + 6);
    NNS_SndArcPlayerStartSeqArcEx(r4, r3, r3, r5, r2b, ipb);
}

void func_020efb64(struct UnkStruct_020efb64 *base, int idx, int code)
{
    struct UnkStruct_020efb64_2 *e = &base->arr[idx];
    if (base->flag == 0) {
        OS_Terminate();
    }
    NNS_SndPlayerSetTrackVolume(e, data_0213e858, e->unk_0A);
    NNS_SndPlayerSetTrackPitch(e, data_0213e858, e->unk_04);
}

void func_020efb54(int value)
{
    data_021fd1a0 = value;
}

void func_020efb44(unsigned int value)
{
    data_021fd19c = value;
}

void func_020efb34(int a)
{
    data_021fd1a4 = a;
}
