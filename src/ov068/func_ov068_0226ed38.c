/* func_ov068_0226ed38 @ 0x0226ed38, 0x64 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221a4f0(void *p);
extern int data_021fbee8[3];

typedef struct {
    char pad_00[0x5c];
    char sub[4];
    char pad_60[0x308 - 0x60];
    int unk_308;
    int unk_30C;
    int unk_310;
    char pad_314[0x378 - 0x314];
    unsigned short unk_378;
    char pad_37A[0x396 - 0x37a];
    unsigned short unk_396;
    unsigned char unk_398;
} UnkStruct_0226ed38;

int func_ov068_0226ed38(UnkStruct_0226ed38 *p)
{
    p->unk_378 &= ~0x10;
    p->unk_378 |= 0x20;
    func_ov003_0221a4f0(&p->sub);
    p->unk_308 = data_021fbee8[0];
    p->unk_30C = data_021fbee8[1];
    p->unk_310 = data_021fbee8[2];
    p->unk_396 = 0;
    p->unk_398 = 0xc;
    return 1;
}
