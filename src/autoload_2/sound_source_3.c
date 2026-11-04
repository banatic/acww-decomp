/* sound_source_3: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f4c4c @ 0x020f4c4c, 0x24 bytes, ARM
 * func_020f4c28 @ 0x020f4c28, 0x24 bytes, ARM
 * func_020f4be8 @ 0x020f4be8, 0x40 bytes, ARM
 * func_020f4ba8 @ 0x020f4ba8, 0x40 bytes, ARM
 */

struct UnkStruct_020f4be8 {
    unsigned char pad_00[8];
    unsigned short unk_08;
    unsigned char flags;
};

typedef struct {
    unsigned char pad_00[8];
    unsigned short unk_08;
    unsigned char unk_0A;
} UnkStruct_020f4ba8;

extern void func_020eed48(void *);
extern int func_020eed18(void *p, int n);
extern void NNS_SndHandleReleaseSeq(void *p);

void func_020f4c4c(void *r0)
{
    func_020eed48((char *) r0 + 4);
    *(unsigned short *) ((char *) r0 + 8) = 0;
    *(unsigned char *) ((char *) r0 + 10) = 0;
}

void func_020f4c28(void *p)
{
    func_020eed18((char *) p + 4, 5);
    NNS_SndHandleReleaseSeq((char *) p + 4);
}

void func_020f4be8(struct UnkStruct_020f4be8 *p, unsigned short v)
{
    if (p->unk_08 != v) {
        p->flags |= 4;
    } else {
        p->flags &= ~4;
    }
    p->unk_08 = v;
    p->flags |= 2;
    p->flags |= 1;
}

void func_020f4ba8(UnkStruct_020f4ba8 *p, unsigned short value)
{
    if (p->unk_08 != value) {
        p->unk_0A |= 4;
    } else {
        p->unk_0A &= ~4;
    }
    p->unk_08 = value;
    p->unk_0A &= ~2;
    p->unk_0A |= 1;
}
