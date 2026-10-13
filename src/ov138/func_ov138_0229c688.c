/* func_ov138_0229c688 @ 0x0229c688, 0x5e bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov138_0229c574(void *self, int cmd);
extern void func_ov002_0220a05c(void *obj, int a, int b, int c, int d);
extern void func_ov002_02208098(void *self, int cmd);
extern void func_ov138_0229c554(void *self, int cmd);

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x94 - 0x8d - 1];
    unsigned char unk_94;
    unsigned char pad_95[0x98 - 0x94 - 1];
} UnkStruct_0229c688;

void func_ov138_0229c688(UnkStruct_0229c688 *self, int a, int b)
{
    if (func_ov138_0229c574(self, 4)) {
        func_ov002_0220a05c((char *) self + 0x98, a, b, 2, 1);
    } else {
        func_ov002_0220a05c((char *) self + 0x98, a, b, 3, 1);
    }
    self->unk_94 = self->unk_8D;
    func_ov002_02208098(self, 8);
    func_ov138_0229c554(self, 4);
}
