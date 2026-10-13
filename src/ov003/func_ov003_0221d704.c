/* func_ov003_0221d704 @ 0x0221d704, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int data[12];
} Chunk;

struct UnkStruct_0221d704 {
    char pad_00[0x1a0];
    Chunk left;
    char pad1[0x235 - (0x1a0 + sizeof(Chunk))];
    unsigned char flag;
    char pad_236[0x318 - (0x235 + 1)];
    Chunk right;
    char pad3[0x36c - (0x318 + sizeof(Chunk))];
    char unk_36C;
    char pad_36D[0x374 - (0x36c + 1)];
    int unk_374;
    char pad_378[0x384 - (0x374 + 4)];
    int *unk_384;
};

extern void func_ov003_022203b8(struct UnkStruct_0221d704 *self);
extern int func_ov003_0221fe9c(void);
extern void func_02056ffc(void *ptr);

int func_ov003_0221d704(struct UnkStruct_0221d704 *self)
{
    func_ov003_022203b8(self);
    if (func_ov003_0221fe9c()) {
        self->right = self->left;
        if ((self->flag & 1) == 0) {
            func_02056ffc(&self->unk_36C);
            *self->unk_384 = self->unk_374;
        }
    }
    return 1;
}
