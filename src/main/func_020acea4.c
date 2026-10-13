/* func_020acea4 @ 0x020acea4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020acea4 UnkStruct_020acea4;
struct UnkStruct_020acea4 {
    char pad_00[0x1c];
    void *unk_1C;
    char pad_20[0x10];
    unsigned int unk_30;
};

extern void *data_021fbe94;
extern void func_020e993c(void *a, void *b);

int func_020acea4(UnkStruct_020acea4 *ptr, void *arg)
{
    if (arg == 0) {
        arg = data_021fbe94;
    }
    if (ptr->unk_1C != 0) {
        func_020e993c(arg, ptr->unk_1C);
        ptr->unk_1C = 0;
    }
    ptr->unk_30 = 0;
    return 0;
}
