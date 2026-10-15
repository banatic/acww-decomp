/* func_ov003_02215894 @ 0x02215894, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205e8d8(void *);
extern int func_0200f328(void *, int);
extern int func_02073908(void *, int);
extern void func_02036460(void *);

extern void *data_020ccf94;
extern void *data_021c526c;

struct UnkStruct_02215894 {
    char pad_00[0x5a0];
    char unk_5A0[0x30];
    unsigned int src[3];
    char pad_5DC[0x600 - 0x5dc];
    unsigned char unk_600;
    char pad_601[0x800 - 0x601];
    unsigned int unk_800;
    char pad_804[0x8c4 - 0x804];
    unsigned int dest0;
    unsigned int dest1;
    unsigned int dest2;
};

void func_ov003_02215894(struct UnkStruct_02215894 *self)
{
    if (func_0205e8d8(self->unk_5A0) == 0) {
        return;
    }
    if (self->unk_600 == 0) {
        return;
    }
    func_0200f328(self, 0x84b);
    {
        unsigned int *p = self->src;
        self->dest0 = p[0];
        self->dest1 = p[1];
        self->dest2 = p[2];
    }
    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        return;
    }
    func_02036460((void *) ((char *) data_021c526c + 0x1c4));
}
