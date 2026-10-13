/* func_02055c80 @ 0x02055c80, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int (*NNS_GfdDefaultFuncAllocTexVram)(int, int, int);
extern int (*NNS_GfdDefaultFuncAllocPlttVram)(int, int, int);

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    char unk_10;
} UnkStruct_02055c80;

int func_02055c80(UnkStruct_02055c80 *self, int a, int b, int c)
{
    if (a) {
        self->unk_04 = NNS_GfdDefaultFuncAllocTexVram(a, 0, 0);
    }
    if (b) {
        self->unk_08 = NNS_GfdDefaultFuncAllocTexVram(b, 1, 0);
    }
    if (c) {
        self->unk_0C = NNS_GfdDefaultFuncAllocPlttVram(c, 0, 0);
    }
    self->unk_10 = 1;
    return 1;
}
