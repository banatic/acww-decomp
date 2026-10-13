/* func_020b5074 @ 0x020b5074, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8328(void *a, unsigned int *b, int *c, signed char **d);
extern void func_020a93e8(void *a, unsigned int b);

typedef struct {
    char pad_00[0x24];
    char *unk_24;
    char unk_28[8];
    unsigned int unk_30;
    char pad_34[0x0c];
    unsigned int unk_40;
    char pad_44;
    char unk_45;
} UnkStruct_020b5074;

void func_020b5074(UnkStruct_020b5074 *self)
{
    unsigned int v0;
    int v1;
    signed char *v2;
    unsigned int r4;
    int r6;

    func_020a8328(&self->unk_28, &v0, &v1, &v2);

    r4 = self->unk_30 - 1;
    r6 = ((0xA00 - self->unk_40) > r4);

    func_020a93e8(self, v0 << 1);

    if (r6) {
        unsigned int i;
        for (i = 0; i < r4; i++) {
            char *p = self->unk_24 + self->unk_40 + i;
            p[0xafc] = v2[i];
        }
        self->unk_40 += r4;
    } else {
        self->unk_45 = 0;
    }
}
