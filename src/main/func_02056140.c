/* func_02056140 @ 0x02056140, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_02056140;

extern void NNS_G3dTexSetTexKey(UnkStruct_02056140 *);
extern void DC_FlushRange(UnkStruct_02056140 *, unsigned int);
extern void NNS_G3dTexLoad(UnkStruct_02056140 *, unsigned int);

int func_02056140(UnkStruct_02056140 *param)
{
    NNS_G3dTexSetTexKey(param);
    DC_FlushRange(param, param->unk_04);
    NNS_G3dTexLoad(param, 1);
    return 1;
}
