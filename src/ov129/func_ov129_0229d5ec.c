/* func_ov129_0229d5ec @ 0x0229d5ec, 0x2a bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

struct func_ov129_0229d5ec_obj {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
};

extern void func_ov002_02207e80(struct func_ov129_0229d5ec_obj *, int, int, int);
extern int func_ov002_02207f60(struct func_ov129_0229d5ec_obj *);

void func_ov129_0229d5ec(struct func_ov129_0229d5ec_obj *self)
{
    func_ov002_02207e80(self, 6, 0, 0);
    self->unk_9C = func_ov002_02207f60(self);
    self->unk_A0 = func_ov002_02207f60(self);
}
