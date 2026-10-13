/* func_0205fcc8 @ 0x0205fcc8, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0205fcc8 {
    char pad_00[0x08];
    int unk_08;
    char pad_0C[0x08];
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
};

extern int func_0205fb28(int *arr, int a, int *b, int *c, int d);
extern void func_0206026c(struct UnkStruct_0205fcc8 *s, int a);

void func_0205fcc8(struct UnkStruct_0205fcc8 *s)
{
    int local_array[3];
    local_array[0] = s->unk_1C;
    local_array[1] = s->unk_20;
    local_array[2] = s->unk_24;
    if (func_0205fb28(local_array, s->unk_14, &s->unk_08, &s->unk_18, 1)) {
        func_0206026c(s, 1);
    }
}
