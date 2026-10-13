/* func_ov144_0229a404 @ 0x0229a404, 0x28 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e930(void *ptr);
extern void func_ov002_0220a580(void *ptr);

typedef struct {
    unsigned char pad_00[0x128];
    char unk_128[4];
} UnkStruct_0229a404;

int func_ov144_0229a404(UnkStruct_0229a404 *self)
{
    if (func_0208e930(self->unk_128)) {
        func_ov002_0220a580(self->unk_128);
        return 1;
    }
    return 0;
}
