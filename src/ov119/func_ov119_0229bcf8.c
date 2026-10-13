/* func_ov119_0229bcf8 @ 0x0229bcf8, 0x46 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9d];
    unsigned char unk_9D;
    char pad_9E[0x1a];
    int count;
} UnkStruct_0229bcf8;

extern void func_ov119_0229ae84(UnkStruct_0229bcf8 *, int);
extern void func_0200277c(int);
extern void func_ov119_0229a69c(UnkStruct_0229bcf8 *, unsigned char);
extern void func_ov002_02208098(UnkStruct_0229bcf8 *, int);

void func_ov119_0229bcf8(UnkStruct_0229bcf8 *self)
{
    if (self->count > 0) {
        self->count--;
        func_ov119_0229ae84(self, self->count);
    } else {
        func_0200277c(4);
        func_ov119_0229a69c(self, self->unk_9D);
        func_ov002_02208098(self, 0xf);
    }
}
