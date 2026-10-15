/* func_ov136_0229d3b4 @ 0x0229d3b4, 0x1e bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char flag;
} UnkStruct_0229d3b4;

extern void func_ov136_0229d00c(UnkStruct_0229d3b4 *self);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);

int func_ov136_0229d3b4(UnkStruct_0229d3b4 *self)
{
    func_ov136_0229d00c(self);
    self->flag = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}
