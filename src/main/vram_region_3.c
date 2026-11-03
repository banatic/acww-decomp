/* vram_region_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02056140 @ 0x02056140, 0x20 bytes, Thumb
 * func_020560e0 @ 0x020560e0, 0x60 bytes, Thumb
 * func_020560c0 @ 0x020560c0, 0x20 bytes, Thumb
 * func_02056084 @ 0x02056084, 0x3c bytes, Thumb
 * func_02056064 @ 0x02056064, 0x1e bytes, Thumb
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_02056140;

typedef struct UnkStruct_020560c0 {
    int unk_00;
    void *unk_04;
} UnkStruct_020560c0;

extern void NNS_G3dTexSetTexKey(UnkStruct_02056140 *, unsigned int, unsigned int);
extern void DC_FlushRange(UnkStruct_02056140 *, unsigned int);
extern void NNS_G3dTexLoad(UnkStruct_02056140 *, unsigned int);
extern int NNS_G3dTexGetRequiredSize(int a);
extern int NNS_G3dTex4x4GetRequiredSize(int a);
extern int func_02055c74(int a, int b);
extern int func_02055c68(int a, int b);
extern int (*NNS_GfdDefaultFuncAllocTexVram)(int, int, int);
extern void func_02105178(UnkStruct_020560c0 *obj, unsigned int key);
extern void NNS_G3dPlttLoad(UnkStruct_020560c0 *obj, int value);
extern unsigned int NNS_G3dPlttGetRequiredSize(void *resource);
extern int func_02055c40(int a, int b);
extern int (*NNS_GfdDefaultFuncAllocPlttVram)(unsigned int, int, int);

int func_02056140(UnkStruct_02056140 *param, unsigned int key, unsigned int key4x4)
{
    NNS_G3dTexSetTexKey(param, key, key4x4);
    DC_FlushRange(param, param->unk_04);
    NNS_G3dTexLoad(param, 1);
    return 1;
}

int func_020560e0(int a, int b)
{
    int v6, v7, v2;
    v6 = NNS_G3dTexGetRequiredSize(a);
    v7 = NNS_G3dTex4x4GetRequiredSize(a);
    if (b) {
        v6 = func_02055c74(b, v6);
        v2 = func_02055c68(b, v7);
    } else {
        v6 = NNS_GfdDefaultFuncAllocTexVram(v6, 0, 0);
        v2 = NNS_GfdDefaultFuncAllocTexVram(v7, 1, 0);
    }
    return func_02056140((UnkStruct_02056140 *) a, v6, v2);
}

int func_020560c0(UnkStruct_020560c0 *obj, unsigned int key)
{
    func_02105178(obj, key);
    DC_FlushRange((UnkStruct_02056140 *) obj, (unsigned int) obj->unk_04);
    NNS_G3dPlttLoad(obj, 1);
    return 1;
}

int func_02056084(void *p0, int p1)
{
    unsigned int size = NNS_G3dPlttGetRequiredSize(p0);
    int r;
    if (p1 != 0) {
        r = func_02055c40(p1, size);
    } else {
        r = NNS_GfdDefaultFuncAllocPlttVram(size, 0, 0);
    }
    return func_020560c0((UnkStruct_020560c0 *) p0, r);
}

int func_02056064(int a, int b)
{
    return func_020560e0(a, b) | func_02056084((void *) a, b);
}
