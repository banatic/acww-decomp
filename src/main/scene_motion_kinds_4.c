/* scene_motion_kinds_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02018db0 @ 0x02018db0, 0x80 bytes, Thumb
 * func_02018d7c @ 0x02018d7c, 0x34 bytes, Thumb
 * func_02018cf0 @ 0x02018cf0, 0x8c bytes, Thumb
 * func_02018ca4 @ 0x02018ca4, 0x4c bytes, Thumb
 */

struct UnkStruct_02018d7c {
    char pad_00[0x190];
    unsigned int unk_190;
    char pad_194[0x216];
    char unk_3AA;
};

typedef struct {
    char pad_00[0x1c];
    unsigned short unk_1C;
} FieldStruct;

extern void *func_02019de4(void *);
extern void func_0201b1a4(void *, void *, int, int, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_0201b044(void *, void *);
extern void func_0201afd4(void *, void *);
extern void func_0201b350(void *, int);
extern void func_02019af0(void *, int);
extern unsigned char data_021fbee8[];
extern int func_0201b354(void *);
extern void func_0200456c(int a);
extern int func_020164cc(void *ptr, int);
extern unsigned short data_020c80f8;

int func_02018db0(void *p0, void *p1)
{
    void *t;
    t = func_02019de4(p0);
    func_0201b1a4((void *) ((char *) p1 + 0x350), p1, 0, 0, *(unsigned short *) ((char *) t + 0x1c));
    func_02016764((void *) ((char *) p1 + 0x334), p1, 0xd8, *(unsigned short *) ((char *) t + 0x1c), 0, 0x1000, 0, 0);
    func_0201b044((void *) ((char *) p1 + 0x350), (void *) data_021fbee8);
    func_0201afd4((void *) ((char *) p1 + 0x350), (void *) data_021fbee8);
    func_0201b350((void *) ((char *) p1 + 0x3aa), -2);
    func_02019af0(p0, 0);
    return 0;
}

void func_02018d7c(void *arg0, struct UnkStruct_02018d7c *arg1)
{
    if (((arg1->unk_190 << 4) >> 16) != 0) {
        return;
    }
    if (func_0201b354(&arg1->unk_3AA) != 0) {
        return;
    }
    func_02019af0(arg0, 1);
}

void func_02018cf0(char *arg0, char *arg1)
{
    FieldStruct *t;
    t = (FieldStruct *) func_02019de4((void *) arg0);
    func_0201b1a4((void *) (arg1 + 0x350), (void *) arg1, 0, 0, t->unk_1C);
    func_0201b044((void *) (arg1 + 0x350), (void *) (((char *) data_021fbee8)));
    func_0201afd4((void *) (arg1 + 0x350), (void *) (((char *) data_021fbee8)));
    func_0201b350((void *) (arg1 + 0x3aa), -2);
    func_02016764((void *) (arg1 + 0x334), (void *) arg1, 0x77, t->unk_1C, 1, 0x1000, 0, 0);
    func_02019af0((void *) arg0, 0);
    func_0200456c(0xa0);
    arg0[0x98] = 0;
}

void func_02018ca4(void *param0, void *param1)
{
    if (func_020164cc((char *) param1 + 0x334, (int) param1)) {
        func_02016764((char *) param1 + 0x334, param1, 0x78, (unsigned short) data_020c80f8, 1, 0x1000, 0, 0);
        *((unsigned char *) param0 + 0x98) = 1;
    }
}
