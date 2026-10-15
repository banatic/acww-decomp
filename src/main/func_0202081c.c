/* func_0202081c @ 0x0202081c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x20];
    unsigned char level;
    unsigned char sublevel;
} UnkStruct_0202081c;
typedef struct {
    int a;
    int b;
} Pair;

extern void func_0201cfb4(void *self, void *local);
extern void func_0201cf90(void *self, void *local, int idx, int a, int b, void *ptr);
extern void func_0201cec8(void *self, void *local);
extern void func_0202da74(void *self, Pair p);
extern void func_02068388(int field, int flag);

extern int data_021c246c;
extern int data_021c24e4;
extern Pair data_020d9420;

void func_0202081c(void *self, int event)
{
    UnkStruct_0202081c local;

    func_0201cfb4(self, &local);
    func_0201cf90(self, &local, 0, 0xc4, 0xc4, &data_021c246c);
    func_0201cf90(self, &local, 1, 0xd0, 0xd0, &data_021c24e4);

    local.level = 2;
    local.sublevel = local.level - 1;

    func_0201cec8(self, &local);
    func_0202da74(self, data_020d9420);
    func_02068388(*(int *) ((char *) self + 0x40), 1);
}
