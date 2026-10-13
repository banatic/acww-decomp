/* func_020198bc @ 0x020198bc, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02019de4(void *a, void *b);
extern void func_0201b1a4(void *a, void *b, int c, int d);
extern void func_0201b044(void *a, void *b);
extern void func_0201afd4(void *a, void *b);
extern void func_0201aff4(void *a, int b);
extern void func_0201b350(void *a, int b);
extern void func_02012444(int a, int b, int c);
extern void func_02019af0(void *a, int b);

extern unsigned char data_021fbee8;
extern unsigned short data_020c80f8;

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char pad_06[14];
    unsigned int unk_14;
    unsigned char pad_18[4];
    unsigned int unk_1C;
} UnkStruct_020198bc;

int func_020198bc(void *first, void *second)
{
    volatile int hw;
    void *ptr;
    int val;

    ptr = func_02019de4(first, second);
    hw = *(unsigned short *) ((char *) ptr + 0x1c);
    func_0201b1a4((char *) second + 0x350, second, 0, 0);
    func_0201b044((char *) second + 0x350, &data_021fbee8);
    func_0201afd4((char *) second + 0x350, &data_021fbee8);
    func_0201aff4((char *) second + 0x350, *(short *) ((char *) second + 0x8e));
    func_0201b350((char *) second + 0x3aa, -2);

    val = *(int *) ((char *) second + 0x628);
    if (val != 0) {
        func_02012444(val, data_020c80f8, 0);
    }

    ((UnkStruct_020198bc *) first)->unk_04 = (unsigned char) ((UnkStruct_020198bc *) first)->unk_1C;
    ((UnkStruct_020198bc *) first)->unk_05 = (unsigned char) ((UnkStruct_020198bc *) first)->unk_14;
    func_02019af0(first, 0);
    return 0;
}
