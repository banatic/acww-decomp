/* func_020b4980 @ 0x020b4980, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x1e];
    unsigned char flag;
    char pad_1F;
    int zone;
    int id;
    char extra[8];
} UnkStruct_020b4980;

typedef int SomeData;
extern SomeData data_020e5308;

typedef int SomeGlobal;
extern SomeGlobal data_021f4dac;

extern void *func_020b4044(UnkStruct_020b4980 *p);
extern void func_020a8164(UnkStruct_020b4980 *p, SomeData *d);
extern void func_020b43f4(SomeGlobal *p);
extern int func_020b4344(SomeGlobal *p, UnkStruct_020b4980 *q);
extern void *func_020b402c(UnkStruct_020b4980 *p);

int func_020b4980(int a, unsigned char *b, SomeData *c)
{
    UnkStruct_020b4980 local;
    int ret;

    if (c == 0) {
        c = &data_020e5308;
    }

    func_020b4044(&local);
    local.zone = 1;
    func_020a8164(&local, c);
    local.flag = *b;
    local.id = a;
    func_020b43f4(&data_021f4dac);
    ret = func_020b4344(&data_021f4dac, &local);
    func_020b402c(&local);
    return ret;
}
