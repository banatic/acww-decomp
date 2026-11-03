/* sky_moon: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c0be4 @ 0x020c0be4, 0x38 bytes, Thumb
 * func_020c0bac @ 0x020c0bac, 0x38 bytes, Thumb
 * func_020c0b88 @ 0x020c0b88, 0x24 bytes, Thumb
 * func_020c0b60 @ 0x020c0b60, 0x28 bytes, Thumb
 * func_020c0b30 @ 0x020c0b30, 0x30 bytes, Thumb
 * func_020c0b1c @ 0x020c0b1c, 0x14 bytes, Thumb
 */

typedef struct UnkStruct_020c0b30 {
    char pad_00[4];
    int unk_04;
    char pad_08[44];
    int unk_34;
} UnkStruct_020c0b30;

extern void func_020c0c58(int);
extern void func_020c0c78(int);
extern void func_020bec14(void *data_021fba00, int k, short *p);
extern short data_021f6cfc[];
extern void func_020c0c1c(int);
extern void func_020bec54(void *ptr, int value);
extern int data_021fba00[];
extern int func_020c0e44(void *param1);
extern unsigned int data_021fbdd0;
extern void func_020bf590(int arg);

void func_020c0be4(int a)
{
    unsigned int i;
    void *p = ((int *) data_021fba00);

    func_020c0c58(a);
    func_020c0c78(a);
    for (i = 0; i < 5; i++) {
        func_020bec14(p, (int) (i + 10), &data_021f6cfc[i]);
    }
}

void func_020c0bac(int a)
{
    unsigned int i;
    void *p = ((int *) data_021fba00);

    func_020c0c1c(a);
    func_020c0c78(a);
    for (i = 0; i < 5; i++) {
        func_020bec14(p, (int) (i + 10), &data_021f6cfc[i]);
    }
}

void func_020c0b88(void)
{
    int *ptr = data_021fba00;
    unsigned int i;
    for (i = 0; i < 5; i++) {
        func_020bec54(ptr, i + 10);
    }
}

void func_020c0b60(void *param1)
{
    void *r4 = param1;
    int result;

    result = func_020c0e44((char *) param1 + 0x34);
    if (result != 0) {
        *(int *) ((char *) r4 + 0xc) = 0x12;
        *(int *) ((char *) r4 + 0x58) = 3;
        func_020c0be4((int) r4);
    } else {
        *(int *) ((char *) r4 + 4) = 3;
    }
}

void func_020c0b30(UnkStruct_020c0b30 *param)
{
    if ((data_021fbdd0 & 0x7f) == 0) {
        if (func_020c0e44(&param->unk_34) == 0) {
            param->unk_04 = 3;
        }
        func_020c0bac((int) param);
    }
}

void func_020c0b1c(int arg)
{
    func_020c0b88();
    func_020bf590(arg);
}
