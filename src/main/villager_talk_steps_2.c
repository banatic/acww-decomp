/* villager_talk_steps_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02023790 @ 0x02023790, 0x64 bytes, Thumb
 * func_0202372c @ 0x0202372c, 0x64 bytes, Thumb
 * func_020236c0 @ 0x020236c0, 0x6c bytes, Thumb
 * func_0202365c @ 0x0202365c, 0x64 bytes, Thumb
 * func_02023634 @ 0x02023634, 0x28 bytes, Thumb
 */

struct UnkStruct_02023790 {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[30];
    unsigned char unk_122;
};

struct Output {
    void *ptr;
    unsigned char byte;
};

struct GlobalData {
    int unk_00;
    unsigned char unk_04;
};

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char pad_104[0x122 - 0x104];
    unsigned char unk_122;
} UnkStruct_0202372c;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0202372c_2;

typedef struct {
    char pad_00[0x20];
    unsigned char level;
    unsigned char sublevel;
} UnkStruct_020236c0;

typedef struct {
    int a;
    int b;
} Pair;

struct UnkStruct_0202365c_2 {
    char pad_00[0x830];
    unsigned int unk_830;
};

struct UnkStruct_0202365c {
    char pad_00[0x100];
    struct UnkStruct_0202365c_2 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_0202365c_3 {
    unsigned int unk_00;
    unsigned char unk_04;
};

struct UnkStruct_0202365c_4 {
    char *data;
    unsigned char length;
};

extern struct GlobalData data_020c89a8;
extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern struct {
    int a;
    unsigned char b;
} data_020c89b8;
extern void func_0201cfb4(void *self, void *local);
extern void func_0201cf90(void *self, void *local, int idx, int a, int b, void *ptr);
extern void func_0201cec8(void *self, void *local);
extern void func_0202da74(void *self, Pair p);
extern void func_02068388(int field, int flag);
extern int data_021c3004;
extern int data_021c2a1c;
extern Pair data_020d8ea0;
extern struct UnkStruct_0202365c_3 data_020c89c0;
extern struct Pair {
    int a;
    int b;
} data_020d9090;
extern void func_020157c8(void *p, int a, int b);
extern int func_02015828(void *p, int a);
extern void func_0202dbf0(void *p, struct Pair pair);

void func_02023790(struct UnkStruct_02023790 *p, struct Output *out)
{
    unsigned char b;
    int result;
    int c;

    b = ((unsigned char *) &data_020c89a8)[4];
    result = func_020036e8((unsigned char *) func_0208150c(*(int *) ((char *) p->unk_100 + 0x830)));
    c = *(int *) &data_020c89a8;
    func_0202da38(p, p->unk_104, &p->unk_122, 30, result, c, b, 2, b);
    out->ptr = p->unk_104;
    out->byte = p->unk_122;
}

void func_0202372c(UnkStruct_0202372c *p, UnkStruct_0202372c_2 *out)
{
    func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 30,
                  func_020036e8((unsigned char *) ((int) func_0208150c(*(int *) ((char *) p->unk_100 + 0x830)))),
                  data_020c89b8.a, data_020c89b8.b, 0, 0);

    out->ptr = (char *) p + 0x104;
    out->byte = p->unk_122;
}

void func_020236c0(void *self)
{
    UnkStruct_020236c0 local;

    func_0201cfb4(self, &local);
    func_0201cf90(self, &local, 0, 0x1f, 0x1f, &data_021c3004);
    func_0201cf90(self, &local, 1, 0x20, 0x20, &data_021c2a1c);

    local.level = 2;
    local.sublevel = local.level - 1;

    func_0201cec8(self, &local);
    func_0202da74(self, data_020d8ea0);
    func_02068388(*(int *) ((char *) self + 0x40), 1);
}

void func_0202365c(struct UnkStruct_0202365c *p, struct UnkStruct_0202365c_4 *out)
{
    unsigned int local0;
    unsigned int local1;
    unsigned int local2;
    unsigned int local3;
    unsigned int local4;

    local0 = (unsigned int) func_020036e8((unsigned char *) (func_0208150c(p->unk_100->unk_830)));
    local1 = data_020c89c0.unk_00;
    local2 = data_020c89c0.unk_04;
    local3 = 0;
    local4 = 0;
    func_0202da38((void *) p, (void *) p->unk_104, (void *) (&p->unk_122), 0x1e, local0, local1, local2, local3, local4);
    out->data = p->unk_104;
    out->length = p->unk_122;
}

void func_02023634(void *arg0, int event)
{
    func_020157c8(arg0, 0x31, 0);
    func_02015828(arg0, 2);
    func_0202dbf0(arg0, data_020d9090);
}
