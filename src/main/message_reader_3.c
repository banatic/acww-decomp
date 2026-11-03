/* message_reader_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b4a20 @ 0x020b4a20, 0x44 bytes, Thumb
 * func_020b49d4 @ 0x020b49d4, 0x4c bytes, Thumb
 * func_020b4980 @ 0x020b4980, 0x54 bytes, Thumb
 * func_020b496c @ 0x020b496c, 0x14 bytes, Thumb
 */

struct UnkStruct_020b4a20 {
    char pad_00[0x1e];
    unsigned char flag;
    char pad_1F[5];
    int value;
    char pad_28[8];
};

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[5];
    int int24;
    unsigned char unk_28;
    unsigned char pad_29[7];
} UnkStruct_020b49d4;

typedef struct {
    char data[0x1e];
    unsigned char flag;
    char pad_1F;
    int zone;
    int id;
    char extra[8];
} UnkStruct_020b4980;

typedef int SomeData;

typedef int SomeGlobal;

struct UnkStruct_020b496c {
    unsigned char pad_00[0x5c];
};

extern int data_021f4dac;
extern void *func_020b4044(struct UnkStruct_020b4a20 *p);
extern void func_020a8164(struct UnkStruct_020b4a20 *p, int p3);
extern void func_020b43f4(int *g);
extern int func_020b4344(int *g, struct UnkStruct_020b4a20 *p);
extern void *func_020b402c(struct UnkStruct_020b4a20 *p);
extern SomeData data_020e5308;
extern void *func_020a8bb8(void *ptr, int arg2);
extern struct UnkStruct_020b496c data_021f62a8[];

int func_020b4a20(int p1, unsigned char *p2, int p3)
{
    struct UnkStruct_020b4a20 local;
    int result;
    func_020b4044(&local);
    func_020a8164(&local, p3);
    local.flag = *p2;
    local.value = p1;
    func_020b43f4(&data_021f4dac);
    result = func_020b4344(&data_021f4dac, &local);
    func_020b402c(&local);
    return result;
}

void *func_020b49d4(int a, unsigned char *b, int c)
{
    UnkStruct_020b49d4 local;
    void *result;
    func_020b4044((struct UnkStruct_020b4a20 *) (&local));
    func_020a8164((struct UnkStruct_020b4a20 *) (&local), c);
    local.unk_1E = *b;
    local.int24 = a;
    local.unk_28 = 1;
    func_020b43f4((int *) (((char *) &data_021f4dac)));
    result = (void *) func_020b4344((int *) (((char *) &data_021f4dac)), (struct UnkStruct_020b4a20 *) (&local));
    func_020b402c((struct UnkStruct_020b4a20 *) (&local));
    return result;
}

int func_020b4980(int a, unsigned char *b, SomeData *c)
{
    UnkStruct_020b4980 local;
    int ret;

    if (c == 0) {
        c = &data_020e5308;
    }

    func_020b4044((struct UnkStruct_020b4a20 *) (&local));
    local.zone = 1;
    func_020a8164((struct UnkStruct_020b4a20 *) (&local), (int) c);
    local.flag = *b;
    local.id = a;
    func_020b43f4((int *) (((SomeGlobal *) &data_021f4dac)));
    ret = func_020b4344((int *) (((SomeGlobal *) &data_021f4dac)), (struct UnkStruct_020b4a20 *) (&local));
    func_020b402c((struct UnkStruct_020b4a20 *) (&local));
    return ret;
}

void *func_020b496c(int idx, int arg2)
{
    return func_020a8bb8(&data_021f62a8[idx], arg2);
}
