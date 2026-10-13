/* func_020efb64 @ 0x020efb64, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);
extern unsigned short data_0213e858;

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

extern void NNS_SndPlayerSetTrackVolume(struct UnkStruct_020efb64_2 *e, unsigned short val, unsigned char b);
extern void NNS_SndPlayerSetTrackPitch(struct UnkStruct_020efb64_2 *e, unsigned short val, short s);

void func_020efb64(struct UnkStruct_020efb64 *base, int idx)
{
    struct UnkStruct_020efb64_2 *e = &base->arr[idx];
    if (base->flag == 0) {
        OS_Terminate();
    }
    NNS_SndPlayerSetTrackVolume(e, data_0213e858, e->unk_0A);
    NNS_SndPlayerSetTrackPitch(e, data_0213e858, e->unk_04);
}
