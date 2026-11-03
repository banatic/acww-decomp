/* villager_talk_nickname_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202af6c @ 0x0202af6c, 0x70 bytes, Thumb
 * func_0202af08 @ 0x0202af08, 0x64 bytes, Thumb
 * func_0202aea0 @ 0x0202aea0, 0x68 bytes, Thumb
 */

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} Param;

struct GlobalData {
    int word;
    unsigned char byte;
};

struct UnkStruct_0202aea0 {
    unsigned char pad_00[0x824];
    unsigned char flag;
};

struct UnkStruct_0202aea0_2 {
    unsigned char pad_00[0x100];
    struct UnkStruct_0202aea0 *inner;
};

struct Pair {
    unsigned int a;
    unsigned int b;
};

extern void func_0201cfb4(void *param, void *buf);
extern void func_0201cf90(void *param, void *buf, int index, int a, int b, void *data);
extern void func_0201cec8(void *param, void *buf);
extern void func_02068388(int value, int flag);
extern void func_0202da74(void *object, Pair value);
extern Pair data_020d8f78;
extern unsigned char data_021c271c[];
extern unsigned char data_021c277c[];
extern int func_0208150c(int arg);
extern int func_020036e8(int arg);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern struct GlobalData data_020c8b18;
extern void MI_CpuFill8(void *, int, int);
extern void func_02015774(struct UnkStruct_0202aea0_2 *, int, void *, int, int);
extern int func_02015828(struct UnkStruct_0202aea0_2 *, int);
extern void func_0202dbf0(struct UnkStruct_0202aea0_2 *, struct Pair);
extern struct Pair data_020d9260;
extern unsigned char data_021c1e84[];

void func_0202af6c(Param *param)
{
    char buf[40];

    func_0201cfb4(param, buf);
    func_0201cf90(param, buf, 0, 0x4b, 0x4f, (void *) data_021c271c);
    func_0201cf90(param, buf, 1, 0x50, 0x54, (void *) data_021c277c);
    buf[32] = 2;
    buf[33] = -1;
    func_0201cec8(param, buf);
    func_0202da74(param, data_020d8f78);
    func_02068388(param->unk_40, 1);
}

void func_0202af08(unsigned char *a, unsigned char *b)
{
    func_0202da38(a, a + 0x104, a + 0x122, 0x1e,
                  func_020036e8(func_0208150c(*(unsigned int *) (*(unsigned int *) (a + 0x100) + 0x830))), data_020c8b18.word,
                  4, 1, data_020c8b18.byte);
    *(unsigned int *) b = (unsigned int) (a + 0x104);
    *(unsigned char *) (b + 4) = *(unsigned char *) (a + 0x122);
}

void func_0202aea0(struct UnkStruct_0202aea0_2 *arg0, int event)
{
    MI_CpuFill8((void *) data_021c1e84, 0, 0x40);
    if (arg0->inner->flag == 0) {
        func_02015774(arg0, 0x15, (void *) data_021c1e84, 4, 0);
    } else {
        func_02015774(arg0, 0x16, (void *) data_021c1e84, 0xa, 0);
    }
    func_02015828(arg0, 6);
    func_0202dbf0(arg0, data_020d9260);
}
