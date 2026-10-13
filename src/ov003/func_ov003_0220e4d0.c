/* func_ov003_0220e4d0 @ 0x0220e4d0, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209129c(int, int);
extern void func_ov003_02220b44(int, int *);

typedef struct {
    char pad_00[0x5c];
    int arr[3];
    char pad_68[0x784];
    int unk_7EC;
    char pad_7F0[0x10];
    int unk_800;
} UnkStruct_0220e4d0;

void func_ov003_0220e4d0(UnkStruct_0220e4d0 *a, int b)
{
    if (a->unk_7EC != -1) {
        func_0209129c(a->unk_7EC, -1);
    }
    if (b == 0x75) {
        return;
    }
    {
        int temp[3];
        int *p = &a->arr[0];
        temp[0] = a->arr[0];
        temp[1] = p[1];
        temp[2] = p[2];
        func_ov003_02220b44(a->unk_800, temp);
    }
}
