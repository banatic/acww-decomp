/* func_ov123_0229c0c0 @ 0x0229c0c0, 0x56 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_0229c0c0;
extern int func_ov002_02207f48(void *, int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern void func_ov123_0229b65c(void *);
extern void func_ov123_0229c044(void *);
void func_ov123_0229c0c0(UnkStruct_0229c0c0 *self)
{
    if (func_ov002_02207f48(self, -1) != 0) {
        func_ov002_022080a0(self, 2);
        func_ov123_0229b65c(self);
        self->unk_98 = 0;
    } else {
        if (self->unk_98 >= 2) {
            self->unk_98 -= 2;
        } else {
            self->unk_98 = 0;
        }
    }
    func_ov123_0229c044(self);
}
