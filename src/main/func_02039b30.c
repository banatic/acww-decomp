/* func_02039b30 @ 0x02039b30, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02039b30_2 {
    int a;
    int b;
} UnkStruct_02039b30_2;

typedef struct UnkStruct_02039b30 {
    char pad_00[0x0c];
    int unk_0C;
    char pad_10[0x04];
    int unk_14;
    int unk_18;
    char unk_1C[0x14];
    char unk_30[0x04];
} UnkStruct_02039b30;

extern UnkStruct_02039b30_2 data_020d5b3c[];
extern void func_0208a1f0(void *base, void *ptr);
extern void func_0208a1ec(void *base, int value);
extern void *func_0208a1e8(void *base, int value);

void func_02039b30(UnkStruct_02039b30 *p)
{
    UnkStruct_02039b30_2 *base = data_020d5b3c;
    UnkStruct_02039b30_2 *ptr18 = base + p->unk_18;

    if (p->unk_0C != 0) {
        func_0208a1f0(&p->unk_1C, base + p->unk_14);
        func_0208a1ec(&p->unk_1C, 1);
        func_0208a1e8(&p->unk_1C, 0);
    }

    func_0208a1f0(&p->unk_30, ptr18);
    func_0208a1ec(&p->unk_30, 1);
    func_0208a1e8(&p->unk_30, 0);
}
