/* sound_slots_3: 7 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ef968 @ 0x020ef968, 0x30 bytes, ARM
 * func_020ef918 @ 0x020ef918, 0x50 bytes, ARM
 * func_020ef8d0 @ 0x020ef8d0, 0x48 bytes, ARM
 * func_020ef8bc @ 0x020ef8bc, 0x14 bytes, ARM
 * func_020ef874 @ 0x020ef874, 0x48 bytes, ARM
 * func_020ef840 @ 0x020ef840, 0x34 bytes, ARM
 * func_020ef7fc @ 0x020ef7fc, 0x44 bytes, ARM
 */

struct UnkStruct_020ef968 {
    int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned char unk_08;
};

struct UnkStruct_020ef8d0 {
    unsigned char pad_00[9];
    unsigned char flags;
};

typedef struct {
    char pad_00[0x34];
    unsigned short unk_34;
} Func020ef874Struct;

extern void NNS_SndPlayerStopSeq(int *p, int q);
extern void OS_Terminate(void);

void func_020ef8d0(struct UnkStruct_020ef8d0 *p, int bit, int mode);

int func_020ef968(struct UnkStruct_020ef968 *p, unsigned char c1, unsigned short c2)
{
    if (p->unk_00 && p->unk_06 == c2 && p->unk_08 == c1) {
        return 1;
    }
    return 0;
}

void func_020ef918(int *p, int q)
{
    if (*p != 0) {
        NNS_SndPlayerStopSeq(p, q);
    }
    func_020ef8d0((struct UnkStruct_020ef8d0 *) p, 2, 0);
    func_020ef8d0((struct UnkStruct_020ef8d0 *) p, 3, 0);
    func_020ef8d0((struct UnkStruct_020ef8d0 *) p, 1, 0);
}

void func_020ef8d0(struct UnkStruct_020ef8d0 *p, int bit, int mode)
{
    if (p == 0) {
        OS_Terminate();
    }
    if (mode == 1) {
        p->flags |= (1u << bit);
    } else {
        p->flags &= ~(1u << bit);
    }
}

int func_020ef8bc(void *p)
{
    unsigned char b = *(unsigned char *) ((char *) p + 9);
    if (b & 4) {
        return 1;
    } else {
        return 0;
    }
}

void func_020ef874(Func020ef874Struct *obj, int bit, int enable)
{
    if (obj == 0) {
        OS_Terminate();
    }
    if (enable == 1) {
        obj->unk_34 |= (1 << bit);
    } else {
        obj->unk_34 &= ~(1 << bit);
    }
}

void func_020ef840(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    if (r0 == 0) {
        OS_Terminate();
    }
    func_020ef874((Func020ef874Struct *) r5, 0, r4);
}

int func_020ef7fc(unsigned char *self)
{
    int i;
    int n;

    n = (int) self[0x36];
    i = 0;
    if (n > 0) {
        do {
            if (*(int *) (self + 8) == 0 && (self[0x11] & 2) == 0) {
                return i;
            }
            i = i + 1;
            self = self + 0xc;
        } while (i < n);
    }
    return n;
}
