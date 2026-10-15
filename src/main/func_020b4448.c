/* func_020b4448 @ 0x020b4448, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    char data[0x1e];
    unsigned char flag;
    char pad_1F;
    int zone;
    int id;
    char extra[8];
} UnkStruct_020b4448;

typedef int SomeData;
typedef int SomeGlobal;
extern SomeGlobal data_021f4dac;
extern void *data_021f669c;
extern SomeData data_020e52e8;

extern void *func_020b4044(UnkStruct_020b4448 *p);
extern void func_020a8164(UnkStruct_020b4448 *p, SomeData *d);
extern void func_020b43f4(SomeGlobal *p);
extern int func_020b4344(SomeGlobal *p, UnkStruct_020b4448 *q);
extern void *func_020b402c(UnkStruct_020b4448 *p);

int func_020b4448(void *self, void *param2, unsigned char *b)
{
    void **pp;
    UnkStruct_020b4448 local;
    int ret;

    func_020b4044(&local);
    func_020a8164(&local, &data_020e52e8);
    local.flag = *b;
    local.id = (int) self;
    local.extra[1] = 1;
    pp = &data_021f669c;
    *pp = param2;
    func_020b43f4(&data_021f4dac);
    ret = func_020b4344(&data_021f4dac, &local);
    *pp = 0;
    func_020b402c(&local);
    return ret;
}
