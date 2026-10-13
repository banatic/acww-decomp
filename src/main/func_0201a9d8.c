/* func_0201a9d8 @ 0x0201a9d8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201aa10(void *p1, void *p2, int p3, int p4, int p5);

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    unsigned char unk_60;
} UnkStruct_0201a9d8;

void func_0201a9d8(UnkStruct_0201a9d8 *self, void *arg2)
{
    func_0201aa10(self, arg2, 4, self->unk_5C, self->unk_60);
}
