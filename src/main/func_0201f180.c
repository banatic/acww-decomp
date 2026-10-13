/* func_0201f180 @ 0x0201f180, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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

extern void func_0201cfb4(void *param, void *local);
extern void func_0201cf90(void *param, void *local, int idx, int max, int val, void *ptr);
extern void func_0201cec8(void *param, void *local);
extern void func_0202da74(void *param, struct Pair p);
extern void func_02068388(int a, int b);
extern struct Pair data_020d9070;

extern unsigned char data_021c25a4[];
extern unsigned char data_021c25ec[];

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
