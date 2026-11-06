/* event_queue_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203ecfc @ 0x0203ecfc, 0x30 bytes, Thumb
 * func_0203ecac @ 0x0203ecac, 0x50 bytes, Thumb
 * func_0203ec98 @ 0x0203ec98, 0x14 bytes, Thumb
 */

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

extern void func_02065c68(void *);
extern void func_0203f53c(void);
extern void func_0203e2a8(int);
extern int data_021c72b8;
extern int data_021c72bc;
extern int data_021c72c4;
extern struct UnkStruct_0203ecac *func_0203f504(void);
extern int func_020b289c(void);

void func_0203ecfc(void)
{
    func_02065c68(&data_021c72c4);
    func_0203f53c();
    data_021c72b8 = 0;
    data_021c72bc = 0;
    func_0203e2a8(6);
}

void func_0203ecac(void)
{
    UnkStruct_0203ecac *obj;
    int result;

    func_0203ecfc();
    obj = func_0203f504();
    result = func_020b289c();
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
    (*(UnkStruct_0203ecac **) &data_021c72b8) = obj;
}

int func_0203ec98(void)
{
    if ((*(unsigned int *) &data_021c72b8)) {
        return 1;
    } else {
        return 0;
    }
}
