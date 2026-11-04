/* heap_2: 6 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e99ac @ 0x020e99ac, 0x2c bytes, ARM
 * func_020e9974 @ 0x020e9974, 0x38 bytes, ARM
 * func_020e9968 @ 0x020e9968, 0xc bytes, ARM
 * func_020e9958 @ 0x020e9958, 0x10 bytes, ARM
 * func_020e9948 @ 0x020e9948, 0x10 bytes, ARM
 * func_020e993c @ 0x020e993c, 0xc bytes, ARM
 */

struct UnkStruct_020e99ac {
    char pad_00[0x6c];
    int index;
};

struct UnkStruct_020e99ac_2 {
    int pad_00;
    struct UnkStruct_020e99ac *ptr;
};

typedef struct UnkStruct_020e9974 {
    char pad_00[0x6c];
    unsigned int unk_6C;
} UnkStruct_020e9974;

typedef struct UnkStruct_020e9974_2 {
    int unk_00;
    UnkStruct_020e9974 *unk_04;
} UnkStruct_020e9974_2;

extern struct UnkStruct_020e99ac_2 OSi_ThreadInfo;
extern int data_021fbe94;
extern int data_021fbe9c[];
extern int func_020e9a08(unsigned int);
extern int func_020e9ed4(int, int, int);
extern void func_020e9c48(void *heap, void *block);

void func_020e99ac(void)
{
    data_021fbe9c[OSi_ThreadInfo.ptr->index] = data_021fbe94;
}

void func_020e9974(void)
{
    unsigned int idx = (*(UnkStruct_020e9974_2 *) &OSi_ThreadInfo).unk_04->unk_6C;
    func_020e9a08(((unsigned int *) data_021fbe9c)[idx]);
    ((unsigned int *) data_021fbe9c)[idx] = 0;
}

int func_020e9968(void *argument0, int argument1, int argument2)
{
    return func_020e9ed4((int) argument0, argument1, argument2);
}

int func_020e9958(int param1, int param2)
{
    return func_020e9ed4(param1, param2, -4);
}

int func_020e9948(int a, int b)
{
    return func_020e9ed4(a, b, 4);
}

void func_020e993c(void *heap, void *block)
{
    func_020e9c48(heap, block);
}
