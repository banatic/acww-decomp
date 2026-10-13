/* func_0202bca0 @ 0x0202bca0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct B_s {
    char pad_00[0x830];
    int unk_830;
} B_s;

typedef struct A_s {
    char pad_00[0x100];
    B_s *unk_100;
    char pad_after[0x24];
    int unk_128;
    int unk_12C;
} A_s;

extern int func_0202d8f8(A_s *a, int *b, int *c, int d, int e);

int func_0202bca0(A_s *a)
{
    return func_0202d8f8(a, &a->unk_12C, &a->unk_128, a->unk_100->unk_830, 0);
}
