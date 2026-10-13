/* func_020f3f88 @ 0x020f3f88, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *p);
extern void func_020f65bc(int a, int b);
extern void func_020f5a3c(void);

extern int data_0213ef80;

struct Global {
    char pad_00[0x30];
    int unk_30;
    char pad_34[0x3f];
    unsigned char unk_73;
};

extern struct Global data_021fd1bc;

struct UnkStruct_020f3f88 {
    void *vtable;
    unsigned char flag;
};

struct UnkStruct_020f3f88 *func_020f3f88(struct UnkStruct_020f3f88 *obj)
{
    func_020f45c4(obj);
    obj->vtable = &data_0213ef80;
    if (data_021fd1bc.unk_30 != 0) {
        func_020f65bc(data_021fd1bc.unk_30, 0xd1);
    }
    obj->flag = 1;
    func_020f5a3c();
    data_021fd1bc.unk_73 = 0;
    return obj;
}
