/* func_ov118_0229c1ec @ 0x0229c1ec, 0x54 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov118_0229a92c(void *);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f60(void *);

typedef struct {
    unsigned char pad_00[0x94];
    int unk_94;
    unsigned short unk_98;
} UnkStruct_0229c1ec;

void func_ov118_0229c1ec(UnkStruct_0229c1ec *self)
{
    func_ov118_0229a92c(self);
    func_ov002_02207f04(self, 10, 0, 0, 0x30);
    func_ov002_02207e80(self, 4, 0, 0);
    func_ov002_02207e80(self, 6, 0, 0x50 - self->unk_98);
    func_ov002_02208090(self, 8);
    self->unk_94 = func_ov002_02207f60(self);
}
