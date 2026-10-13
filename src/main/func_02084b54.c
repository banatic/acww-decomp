/* func_02084b54 @ 0x02084b54, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f8ec(void *);
extern void func_02084d84(void *);

typedef struct {
    char unk_00[0x70];
    unsigned char unk_70;
    void *unk_74;
} UnkStruct_02084b54;

void func_02084b54(UnkStruct_02084b54 *self)
{
    if (self->unk_70) {
        func_0204f8ec(self->unk_74);
        func_02084d84(self);
    }
}
