/* func_ov122_0229fea4 @ 0x0229fea4, 0x38 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    char pad_A0[10];
    char unk_AA;
} UnkStruct_0229fea4;

extern int func_ov122_0229fe28(void *self, int a, void *b);
extern void func_ov122_0229efd8(void *self, int a);
extern void func_ov122_0229f590(void *self, int a);
extern void func_ov122_0229fa90(void *self);

void func_ov122_0229fea4(UnkStruct_0229fea4 *self)
{
    int result = func_ov122_0229fe28(self, self->unk_9C, &self->unk_AA);
    func_ov122_0229efd8(self, 0x1000);
    func_ov122_0229f590(self, result);
    func_ov122_0229fa90(self);
}
