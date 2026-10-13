/* func_0208bc30 @ 0x0208bc30, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
} UnkStruct_0208bc30;

typedef struct {
    char pad_00[0xC];
    UnkStruct_0208bc30 unk_0C;
    char pad_10[0x10];
    int unk_20;
} UnkStruct_0208bc30_2;

extern void func_0208a1f0(UnkStruct_0208bc30 *dst, void *src);
extern void func_0208a1ec(UnkStruct_0208bc30 *dst, int val);
extern void func_0208a144(UnkStruct_0208bc30 *dst);
extern char data_020d5c44[];

void func_0208bc30(UnkStruct_0208bc30_2 *s)
{
    s->unk_20 = 6;
    func_0208a1f0(&s->unk_0C, data_020d5c44);
    func_0208a1ec(&s->unk_0C, 1);
    func_0208a144(&s->unk_0C);
}
