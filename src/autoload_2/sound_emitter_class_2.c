/* sound_emitter_class_2: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f5690 @ 0x020f5690, 0x14 bytes, ARM
 * func_020f564c @ 0x020f564c, 0x44 bytes, ARM
 * func_020f560c @ 0x020f560c, 0x40 bytes, ARM
 * func_020f55cc @ 0x020f55cc, 0x40 bytes, ARM
 */

struct UnkStruct_020f560c;

typedef struct UnkStruct_020f560c {
    void *unk_00;
    unsigned char pad_04[0x30];
    void (*unk_34)(void *, int, int);
    unsigned char pad_38[0x06];
    unsigned char unk_3E;
    unsigned char unk_3F;
} UnkStruct_020f560c;

struct UnkStruct_020f55cc {
    void *unk_00;
    unsigned char pad_04[0x30];
    void (*unk_34)(void *, int, int);
    unsigned char pad_38[0x6];
    unsigned char unk_3E;
    unsigned char unk_3F;
};

extern void func_020ef754(int *p);
extern void NNS_SndPlayerStopSeqBySeqArcIdx(int, int, int);
extern void func_020f5970(struct UnkStruct_020f560c *self);
extern void func_020f555c(void *sound, int index, int code);
extern char data_020d8414;

void func_020f5690(int *p)
{
    if (p) {
        p++;
    }
    func_020ef754(p);
}

void func_020f564c(void *receiver)
{
    int r4 = 0;
    int r5 = 2;
    int r6 = 0x52;
    while (r6 < 0x61) {
        NNS_SndPlayerStopSeqBySeqArcIdx(r5, r6, r4);
        r6++;
    }
    NNS_SndPlayerStopSeqBySeqArcIdx(2, 0x36, 0);
}

struct UnkStruct_020f560c *func_020f560c(struct UnkStruct_020f560c *self)
{
    func_020f5970(self);
    self->unk_00 = &data_020d8414;
    self->unk_34 = func_020f555c;
    self->unk_3E = 1;
    self->unk_3F = 0;
    return self;
}

struct UnkStruct_020f55cc *func_020f55cc(struct UnkStruct_020f55cc *self)
{
    func_020f5970((struct UnkStruct_020f560c *) self);
    self->unk_00 = &data_020d8414;
    self->unk_34 = func_020f555c;
    self->unk_3E = 1;
    self->unk_3F = 0;
    return self;
}
