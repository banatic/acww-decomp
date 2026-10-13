/* func_0208cbb8 @ 0x0208cbb8, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x28];
    void *unk_28;
    unsigned char pad_2C[0x24];
    unsigned char unk_50[0x55];
    unsigned char unk_A5;
    unsigned char pad_A6[0x1a];
    unsigned char unk_C0;
} UnkStruct_0208cbb8;

extern void func_020b45d0(void *a, unsigned char b, int c, int d, int e, int f);
extern void func_02051694(void *arg);

void func_0208cbb8(UnkStruct_0208cbb8 *s)
{
    if (s->unk_A5 == 0) {
        return;
    }
    if (s->unk_28 == 0) {
        return;
    }
    func_020b45d0(&s->unk_50, s->unk_C0, 2, 6, 0, 1);
    func_02051694(s->unk_28);
    s->unk_A5 = 0;
}
