/* func_0203ecac @ 0x0203ecac, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ecfc(void);
extern struct UnkStruct_0203ecac *func_0203f504(void);
extern int func_020b289c(struct UnkStruct_0203ecac *p);

typedef struct UnkStruct_0203ecac {
    char pad_00[8];
    char unk_08;
    char pad_09[3];
    int unk_0C;
    int unk_10;
    char unk_14;
    char unk_15;
    char unk_16;
    char unk_17;
} UnkStruct_0203ecac;

extern UnkStruct_0203ecac *data_021c72b8;

void func_0203ecac(void)
{
    UnkStruct_0203ecac *obj;
    int result;

    func_0203ecfc();
    obj = func_0203f504();
    result = func_020b289c(obj);
    if (result != 0) {
        obj->unk_0C = result;
        obj->unk_10 = 0;
        obj->unk_15 = 12;
        obj->unk_14 = 2;
        obj->unk_16 = 7;
    } else {
        obj->unk_0C = 0;
        obj->unk_10 = 0;
        obj->unk_15 = 4;
        obj->unk_14 = 3;
        obj->unk_16 = 5;
    }
    obj->unk_08 = 1;
    obj->unk_17 = 5;
    data_021c72b8 = obj;
}
