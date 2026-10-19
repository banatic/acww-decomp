/* func_ov102_0229c318 @ 0x0229c318, 0x4c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c318 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x218c - 0x8d];
    unsigned char unk_218C;
    unsigned char pad_218D[0x25aa - 0x218d];
    unsigned char unk_25AA;
} UnkStruct_0229c318;

extern int func_ov002_02207d24(void *, int);
extern void func_ov102_0229cb50(UnkStruct_0229c318 *);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern unsigned short data_ov102_0229e95c[];
extern void func_0200467c(int command);
extern void func_ov102_0229c298(UnkStruct_0229c318 *, int);

void func_ov102_0229c318(UnkStruct_0229c318 *obj)
{
    func_ov002_02207d24(&obj->unk_218C, 1);
    func_ov102_0229cb50(obj);
    obj->unk_8C = 7;
    func_ov002_022080a0(obj, 1);
    func_0200467c(data_ov102_0229e95c[obj->unk_25AA]);
    func_ov102_0229c298(obj, 0x40);
}
