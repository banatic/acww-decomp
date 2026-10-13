/* func_020a8658 @ 0x020a8658, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a8658 {
    unsigned char pad_00[0xc];
    void *unk_0C;
};
extern unsigned char func_020a87c8(void *, int);

void func_020a8658(struct UnkStruct_020a8658 *s, unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d,
                   unsigned char *e)
{
    *a = func_020a87c8(s->unk_0C, 0);
    *b = func_020a87c8(s->unk_0C, 1);
    *c = func_020a87c8(s->unk_0C, 2);
    *d = func_020a87c8(s->unk_0C, 3);
    *e = func_020a87c8(s->unk_0C, 4);
}
