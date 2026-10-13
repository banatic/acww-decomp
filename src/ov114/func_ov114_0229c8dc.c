/* func_ov114_0229c8dc @ 0x0229c8dc, 0x48 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov114_0229ccc0(void *, unsigned short);
extern void func_ov114_0229c890(void *);
extern void func_ov114_0229ce18(void *, int, int);
extern void func_02001a04(unsigned int, unsigned int, int);

typedef struct {
    unsigned char pad_00[0x12a4];
    unsigned int unk_12A4;
    unsigned int unk_12A8;
    unsigned char pad_12AC[0x0d];
    unsigned char unk_12B9;
    unsigned char unk_12BA;
} UnkStruct_0229c8dc;

void func_ov114_0229c8dc(UnkStruct_0229c8dc *self)
{
    self->unk_12B9 = 0xff;
    self->unk_12BA = 0;
    func_ov114_0229ccc0(self, 0xff);
    func_ov114_0229c890(self);
    func_ov114_0229ce18(self, 0, 0x10);
    func_02001a04(self->unk_12A8, self->unk_12A4, 0);
}
