/* func_020f96b0 @ 0x020f96b0, 0x78 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int SND_RecvCommandReply(int);
extern int func_0210aa44(void);
extern int SND_FlushCommand(int);
extern int func_0210b4cc(void *, void *);
extern int FX_Div(int, int);

extern int data_021fd1f8;

typedef struct {
    int unk_00;
    int unk_04;
    unsigned char pad[6];
    short unk_0E;
} Param;

typedef struct {
    unsigned char pad[6];
    unsigned short val;
    unsigned char pad_08[8];
} UnkStruct_020f96b0;

void func_020f96b0(Param *param)
{
    UnkStruct_020f96b0 local;
    int zero = 0;
    int *p = &data_021fd1f8;

    do {
    } while (SND_RecvCommandReply(zero) != 0);

    func_0210aa44();
    SND_FlushCommand(0);

    if (func_0210b4cc(p, &local) == 0) {
        return;
    }

    param->unk_0E = local.val;
    param->unk_04 = FX_Div(0x258000, param->unk_0E << 12);
}
