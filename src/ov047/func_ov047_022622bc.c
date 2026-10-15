/* func_ov047_022622bc @ 0x022622bc, 0x40 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_020912d4(int a, char *b, char *c, int _x);
extern void func_02091278(void *, void *, void *, void *);

typedef struct UnkStruct_022622bc {
    char pad_00[0x8e];
    char buf[0x478 - 0x8e];
    char unk_478;
    char pad_479[0x73c - 0x479];
    int unk_73C;
} UnkStruct_022622bc;

int func_ov047_022622bc(UnkStruct_022622bc *self)
{
    int v = self->unk_73C;
    if (v == -1) {
        self->unk_73C = func_020912d4(0x3c, &self->unk_478, self->buf, 0);
    } else {
        func_02091278((void *) (v), (void *) (&self->unk_478), (void *) (self->buf), 0);
    }
    return 1;
}