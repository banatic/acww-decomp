/* villager_talk_nickname_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202a8e8 @ 0x0202a8e8, 0x58 bytes, Thumb
 * func_0202a8a4 @ 0x0202a8a4, 0x44 bytes, Thumb
 */

struct UnkStruct_0202a8e8 {
    char pad_00[0x830];
    void *unk_830;
};

struct UnkStruct_0202a8e8_2 {
    char pad_00[0x100];
    struct UnkStruct_0202a8e8 *inner;
};

struct Result {
    void *ptr;
    char byte;
};

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

extern unsigned int func_0208150c(void *p);
extern int func_0200368c(void *ptr, int a, int b, int c);
extern int func_020036e8(unsigned char *);
extern int data_020c8b20;
extern char data_021c1e84[];
extern Pair data_020d9178;
extern void MI_CpuFill8(void *dst, int fill, int len);
extern void func_02015774(void *a, int b, void *c, int d, int e);
extern int func_02015828(void *a, int b);
extern void func_0202dbf0(void *a, Pair arg);

void func_0202a8e8(struct UnkStruct_0202a8e8_2 *a, struct Result *b)
{
    int tmp;
    unsigned char *p;

    tmp = func_020036e8((unsigned char *) func_0208150c(a->inner->unk_830));
    func_0200368c((char *) a + 0x104, 0x1e, data_020c8b20, tmp);
    p = (unsigned char *) a + 0x122;
    *p = 3;
    b->ptr = (void *) ((char *) a + 0x104);
    b->byte = *p;
}

void func_0202a8a4(void *p, int event)
{
    MI_CpuFill8(data_021c1e84, 0, 0x40);
    func_02015774(p, 0x11, data_021c1e84, 6, 0);
    func_02015828(p, 6);
    func_0202dbf0(p, data_020d9178);
}
