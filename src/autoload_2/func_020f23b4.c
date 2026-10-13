/* func_020f23b4 @ 0x020f23b4, 0x108 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);
extern void *NNS_SndHeapCreate(const char *, int);
extern void func_020eeea4(char *, char *, void *, int);
extern int CARD_GetThreadPriority(void);
extern void NNS_SndCaptureCreateThread(int);
extern void func_020f2344(void *);
extern void func_0210ab38(int);
extern int func_020eef70(void);
extern void func_0210fe08(int, int);
extern void func_020eecb0(int);
extern void func_0210fbf8(void *);
extern void ENV_AppendResourceSet(void *);

typedef struct {
    int unk_00;
    char pad_04[0x24];
    volatile void *unk_28;
    char pad_2C[0x8];
    char unk_34[4];
    char unk_38[4];
    char unk_3C[4];
    char unk_40[4];
    char pad_44[0x4];
    char unk_48[4];
    char pad_4C[0x4];
    int unk_50;
    char pad_54[0x10];
    short unk_64;
    int unk_68;
    short unk_6C;
    short unk_6E;
    char unk_70;
    char unk_71;
} UnkStruct_020f23b4;

void func_020f23b4(UnkStruct_020f23b4 *self, char *p1, char *p2, void *p3)
{
    self->unk_28 = 0;
    if (self->unk_28 != 0) {
        OS_Terminate();
    }
    self->unk_28 = NNS_SndHeapCreate(p1, 0x339c);
    if (self->unk_28 == 0) {
        OS_Terminate();
    }
    func_020eeea4(p1 + 0x339c, p2 - 0x339c, p3, 0);
    NNS_SndCaptureCreateThread(CARD_GetThreadPriority() - 1);
    self->unk_50 = 1;
    func_020f2344(self);
    func_0210ab38(0x7f);
    func_0210fe08(0xa, func_020eef70());
    func_0210fbf8(&self->unk_34);
    func_020eecb0(0);
    ENV_AppendResourceSet(&self->unk_48);
    ENV_AppendResourceSet(&self->unk_38);
    ENV_AppendResourceSet(&self->unk_3C);
    ENV_AppendResourceSet(&self->unk_40);
    self->unk_00 = 0;
    self->unk_64 = 0;
    self->unk_68 = 0;
    self->unk_6C = -1;
    self->unk_6E = 0;
    self->unk_70 = 0;
    self->unk_71 = 0;
}
