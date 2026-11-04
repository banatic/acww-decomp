/* sound_system_11: 8 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f24bc @ 0x020f24bc, 0x44 bytes, ARM
 * func_020f23b4 @ 0x020f23b4, 0x108 bytes, ARM
 * func_020f2388 @ 0x020f2388, 0x2c bytes, ARM
 * func_020f2378 @ 0x020f2378, 0x10 bytes, ARM
 * func_020f2368 @ 0x020f2368, 0x10 bytes, ARM
 * func_020f2354 @ 0x020f2354, 0x14 bytes, ARM
 * func_020f2344 @ 0x020f2344, 0x10 bytes, ARM
 * func_020f2338 @ 0x020f2338, 0xc bytes, ARM
 */

typedef unsigned int uint32_t;

typedef unsigned char uint8_t;

typedef unsigned long long uint64_t;

struct UnkStruct_020f24bc;

struct UnkStruct_020f24bc {
    char pad_00[0x4d];
    uint8_t unk_4D;
    char pad_4E[6];
    uint32_t unk_54;
    uint64_t unk_58;
    uint8_t unk_60;
    uint8_t pad_61;
    uint8_t unk_62;
};

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

typedef struct {
    unsigned char pad_00[0x50];
    int unk_50;
} UnkStruct_020f2344;

extern uint64_t OS_GetTick(void);
extern void OS_Terminate(void);
extern void *NNS_SndHeapCreate(const char *, int);
extern void func_020eeea4(char *, char *, void *, int);
extern int CARD_GetThreadPriority(void);
extern void NNS_SndCaptureCreateThread(int);
extern void func_0210ab38(int);
extern int func_020eef70(void);
extern void func_0210fe08(int, int);
extern int func_020eecb0(int);
extern void func_0210fbf8(void *);
extern void func_020eed48(void *);
extern void func_020eedfc(void);
extern void func_020f0d3c(void *receiver);
extern void func_020f1520(void *arg);
extern void func_020f13bc(void *arg);
extern void NNS_SndCaptureChangeOutputEffect(int effect);
extern void func_020eee5c(int arg);
extern void NNS_SndCaptureStopEffect(void);

void func_020f2344(UnkStruct_020f2344 *self);

struct UnkStruct_020f24bc *func_020f24bc(struct UnkStruct_020f24bc *s)
{
    s->unk_54 = OS_GetTick();
    s->unk_58 = 0x00269ec35d588b65ULL;
    s->unk_4D = 0;
    s->unk_60 = 0;
    s->unk_62 = 0;
    return s;
}

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
    func_020f2344((UnkStruct_020f2344 *) self);
    func_0210ab38(0x7f);
    func_0210fe08(0xa, func_020eef70());
    func_0210fbf8(&self->unk_34);
    func_020eecb0(0);
    func_020eed48(&self->unk_48);
    func_020eed48(&self->unk_38);
    func_020eed48(&self->unk_3C);
    func_020eed48(&self->unk_40);
    self->unk_00 = 0;
    self->unk_64 = 0;
    self->unk_68 = 0;
    self->unk_6C = -1;
    self->unk_6E = 0;
    self->unk_70 = 0;
    self->unk_71 = 0;
}

void func_020f2388(void *arg)
{
    func_020eedfc();
    func_020f0d3c(arg);
    func_020f1520(arg);
    func_020f13bc(arg);
}

void func_020f2378(void *context)
{
    func_0210ab38(0);
}

void func_020f2368(void)
{
    func_0210ab38(0x7f);
}

void func_020f2354(void *self, int effect)
{
    struct UnkStruct_020f2354 {
        char pad[0x50];
        volatile int field;
    } *p = (struct UnkStruct_020f2354 *) self;

    p->field = effect;
    NNS_SndCaptureChangeOutputEffect(p->field);
}

void func_020f2344(UnkStruct_020f2344 *self)
{
    func_020eee5c(self->unk_50);
}

void func_020f2338(void *receiver)
{
    NNS_SndCaptureStopEffect();
}
