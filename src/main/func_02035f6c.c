/* func_02035f6c @ 0x02035f6c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02004260(int arg);
extern void func_02004270(unsigned short arg);
extern void func_02035820(void *addr, unsigned short arg);
extern void func_0200424c(int arg1, int arg2);
extern char *data_021c526c;

struct UnkStruct_02035f6c {
    char pad_00[4];
    unsigned char flag4;
    char pad_05;
    unsigned short unk_06;
    unsigned char flag8;
    char pad_09;
    char pad_0A;
    char pad_0B;
    int unk_0C;
    unsigned char flag10;
    char pad_11;
    char pad_12;
    char pad_13;
    int unk_14;
    int unk_18;
};

void func_02035f6c(struct UnkStruct_02035f6c *obj)
{
    if (obj->flag8) {
        obj->flag8 = 0;
        func_02004260(obj->unk_0C);
    }
    if (obj->flag4) {
        obj->flag4 = 0;
        func_02004270(obj->unk_06);
        func_02035820(data_021c526c + 0x2f0, obj->unk_06);
    }
    if (obj->flag10) {
        obj->flag10 = 0;
        func_0200424c(obj->unk_14, obj->unk_18);
    }
}
