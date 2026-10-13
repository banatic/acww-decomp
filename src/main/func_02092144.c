/* func_02092144 @ 0x02092144, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int a, int b);
extern void func_02094bc0(void *self);
extern short data_021d5658[];

typedef struct {
    unsigned char pad_00[0xc];
    void *sub;
} UnkStruct_02092144;

typedef struct {
    unsigned char pad_00[0x44];
    int unk_44;
    unsigned char pad_48[8];
    int unk_50;
} UnkStruct_02092144_2;

void func_02092144(UnkStruct_02092144 *self)
{
    short x = data_021d5658[8];
    short v1 = (short) ((short) FX_MulFunc(0x1333, x) + 0x4cd);
    short v2 = (short) ((short) FX_MulFunc(0x3ae, x) + 0x800);
    func_02094bc0(self);
    ((UnkStruct_02092144_2 *) self->sub)->unk_44 = v1;
    ((UnkStruct_02092144_2 *) self->sub)->unk_50 = v2;
}
