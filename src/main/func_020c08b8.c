/* func_020c08b8 @ 0x020c08b8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xC];
    int unk_0C;
    char pad_10[0x48];
    int unk_58;
    char pad_5C[0x4];
    int unk_60;
    int unk_64;
    int unk_68;
} UnkStruct_020c08b8;

extern int func_020644cc(int arg);
extern void func_020bf568(UnkStruct_020c08b8 *obj, int flag, unsigned int size);
extern void func_0209f128(const void *ptr, int num);

extern unsigned char data_021dc7a8[];

void func_020c08b8(UnkStruct_020c08b8 *obj)
{
    int flag;
    if (func_020644cc(2) == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    func_020bf568(obj, flag, 0x1000);
    obj->unk_0C = 0x16;
    obj->unk_58 = 2;
    func_0209f128((void *) data_021dc7a8, 9);
    obj->unk_60 = 0;
    obj->unk_64 = 0;
    obj->unk_68 = 0;
}
