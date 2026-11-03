/* villager_talk_lines_4: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201f25c @ 0x0201f25c, 0x8 bytes, Thumb
 * func_0201f254 @ 0x0201f254, 0x8 bytes, Thumb
 * func_0201f1f0 @ 0x0201f1f0, 0x64 bytes, Thumb
 * func_0201f180 @ 0x0201f180, 0x70 bytes, Thumb
 * func_0201f150 @ 0x0201f150, 0x30 bytes, Thumb
 */

#define Predicate_0201f520 ((int (*)(unsigned short *, int)) func_0201f520)

struct UnkStruct_0201f1f0 {
    char *ptr;
    unsigned char byte;
};

struct Pair {
    int a;
    int b;
};

struct UnkStruct_0201f180 {
    char data[0x20];
    unsigned char unk_20;
    unsigned char unk_21;
    char pad[6];
};

struct Param {
    char pad[0x40];
    int unk_40;
};

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0201f150;

extern void func_0202a5e8(void *, void *);
extern void func_02020360(void *);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern int data_020c8ba0;
extern void func_0201cfb4(void *param, void *local);
extern void func_0201cf90(void *param, void *local, int idx, int max, int val, void *ptr);
extern void func_0201cec8(void *param, void *local);
extern void func_0202da74(void *param, struct Pair p);
extern void func_02068388(int a, int b);
extern struct Pair data_020d9070;
extern unsigned char data_021c25a4[];
extern unsigned char data_021c25ec[];
extern unsigned short func_0201f520(unsigned short *, int);
extern void func_020157d4(void *, int (*)(unsigned short *, int), unsigned char, unsigned char);
extern int func_02015828(void *obj, int a);
extern void func_0202dbf0(void *obj, UnkStruct_0201f150 arg);
extern UnkStruct_0201f150 data_020d8e28;

void func_0201f25c(void *argument0, void *argument1)
{
    func_0202a5e8((void *) argument0, (void *) argument1);
}

void func_0201f254(void *argument0)
{
    func_02020360((void *) argument0);
}

void func_0201f1f0(void *a, struct UnkStruct_0201f1f0 *b)
{
    int v0;
    int v1;

    v0 = func_020036e8(func_0208150c(*(int *) (*(int *) ((char *) a + 0x100) + 0x830)));
    v1 = data_020c8ba0;
    func_0202da38(a, (char *) a + 0x104, (char *) a + 0x122, 30, v0, v1, 1, 13, 2);
    b->ptr = (char *) a + 0x104;
    b->byte = *((unsigned char *) a + 0x122);
}

void func_0201f180(struct Param *param)
{
    struct UnkStruct_0201f180 local;
    func_0201cfb4(param, &local);
    func_0201cf90(param, &local, 0, 0x5b, 0x5d, (void *) data_021c25a4);
    func_0201cf90(param, &local, 1, 0x5e, 0x60, (void *) data_021c25ec);
    local.unk_20 = 2;
    local.unk_21 = local.unk_20 - 1;
    func_0201cec8(param, &local);
    func_0202da74(param, data_020d9070);
    func_02068388(param->unk_40, 1);
}

void func_0201f150(void *obj)
{
    func_020157d4(obj, Predicate_0201f520, 13, 1);
    func_02015828(obj, 0);
    func_0202dbf0(obj, data_020d8e28);
}
