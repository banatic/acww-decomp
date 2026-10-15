/* func_0208dc88 @ 0x0208dc88, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0208dc88 {
    char data[0x14];
} UnkStruct_0208dc88;

typedef struct SomeElement {
    int a;
    int b;
} SomeElement;

typedef struct UnkStruct_0208dc88_2 {
    char pad_00[0x0c];
    UnkStruct_0208dc88 sub;
    int unk_20;
    char pad_24[0x2b];
    unsigned char unk_4F;
} UnkStruct_0208dc88_2;

extern void func_0208d400(UnkStruct_0208dc88_2 *self);
extern void func_0208a1f0(UnkStruct_0208dc88 *sub, const SomeElement *elem);
extern void func_0208a1ec(UnkStruct_0208dc88 *sub, int val);
extern void *func_0208a144(UnkStruct_0208dc88 *sub);
extern void func_0208db08(UnkStruct_0208dc88_2 *self);
extern SomeElement data_020d5b3c[];

void func_0208dc88(UnkStruct_0208dc88_2 *self)
{
    int idx;

    self->unk_20 = 1;
    func_0208d400(self);

    if (self->unk_4F != 0) {
        idx = 0x29;
    } else {
        idx = 4;
    }

    func_0208a1f0(&self->sub, &data_020d5b3c[idx]);
    func_0208a1ec(&self->sub, 1);
    func_0208a144(&self->sub);
    func_0208db08(self);
}
