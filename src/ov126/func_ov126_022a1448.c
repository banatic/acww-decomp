/* func_ov126_022a1448 @ 0x022a1448, 0x30 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a1448 {
    char pad_00[0xb0];
    int unk_B0;
    char pad_B4[0x3d10];
    int unk_3DC4;
    char pad_3DC8[0x22c];
    int unk_3FF4;
} UnkStruct_022a1448;

extern void func_ov126_0229f7a8(UnkStruct_022a1448 *p, int n);
extern void func_ov124_0229eea0(int *p);
extern void func_ov002_0220af74(int *p);
extern void func_02070b84(int *p);

void func_ov126_022a1448(UnkStruct_022a1448 *self)
{
    func_ov126_0229f7a8(self, 0x10);
    func_ov124_0229eea0(&self->unk_B0);
    func_ov002_0220af74(&self->unk_3DC4);
    func_02070b84(&self->unk_3FF4);
}
