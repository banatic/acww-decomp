/* func_ov122_0229f9e8 @ 0x0229f9e8, 0x4c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051d08(void *, int);

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    char pad_A4[0x8];
    unsigned char unk_AC;
    char pad_AD[0xf];
    void *unk_BC;
} UnkStruct_0229f9e8;

int func_ov122_0229f9e8(UnkStruct_0229f9e8 *p)
{
    int ret1;
    int ret2;

    ret1 = func_02051d08((char *) p->unk_BC + 0xd8, p->unk_AC);
    p->unk_9C = (unsigned char) (ret1 + 0x30);
    ret2 = func_02051d08((char *) p->unk_BC + 0xd8, 0x10);
    p->unk_9C = p->unk_9C + (0xA0 - ret2);
    p->unk_A0 = 0x88;
    return 0x88;
}
