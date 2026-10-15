/* func_02021df0 @ 0x02021df0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02021e44(int unused, int x);

extern int func_02021ea8(void *self, int *arr, int count, void *predicate);
extern int func_02081d64(int);
extern void *func_02015e70(void *a, int b, int c);
extern int func_02021e68(int a);
extern void func_02015fb0(void *a, int b, int c, int d, int e, int f);

struct UnkStruct_02021df0 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_02021df0_2 {
    char pad_00[0x100];
    struct UnkStruct_02021df0 *inner;
};

int func_02021df0(struct UnkStruct_02021df0_2 *param0, int param1, int param2)
{
    int result;
    int temp;
    result = func_02021ea8((void *) (param0->inner->unk_830), (int *) (param1), (int) (param2), (((void *) func_02021e44)));
    if (result != 0) {
        temp = func_02081d64(result);
        func_02015e70(param0, temp, 9);
        temp = func_02021e68(result);
        func_02015fb0(param0, temp, 0, 0xa, 0, 0);
    }
    return result;
}
