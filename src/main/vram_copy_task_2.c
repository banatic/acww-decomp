/* vram_copy_task_2: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ba1b0 @ 0x020ba1b0, 0xa bytes, Thumb
 * func_020ba1a8 @ 0x020ba1a8, 0x8 bytes, Thumb
 * func_020ba184 @ 0x020ba184, 0x24 bytes, Thumb
 * func_020ba160 @ 0x020ba160, 0x24 bytes, Thumb
 * func_020ba13c @ 0x020ba13c, 0x22 bytes, Thumb
 * func_020ba12c @ 0x020ba12c, 0x10 bytes, Thumb
 * func_020ba128 @ 0x020ba128, 0x4 bytes, Thumb
 * func_020ba118 @ 0x020ba118, 0x10 bytes, Thumb
 */

typedef struct {
    unsigned int unk_00;
    void *unk_04;
    unsigned int unk_08;
} UnkStruct_020ba184;

typedef struct ObjStruct ObjStruct;

struct ObjStruct {
    int pad_00;
    int unk_04;
};

typedef struct {
    int pad_00;
    ObjStruct *ptr;
} UnkStruct_020ba13c;

extern void DC_FlushRange(void *, unsigned int);
extern void GX_BeginLoadTex(void);
extern void GX_LoadTex(const void *, unsigned int, unsigned int);
extern void GX_EndLoadTex(void);
extern void GX_BeginLoadTexPltt(void);
extern void GX_LoadTexPltt(unsigned int a, unsigned int b, unsigned int c);
extern void GX_EndLoadTexPltt(void);
extern void NNS_G3dTexLoad(ObjStruct *obj, int arg);
extern void NNS_G3dPlttLoad(ObjStruct *obj, int arg);

void func_020ba1b0(int *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}

void func_020ba1a8(int *p0, int p1, int p2, int p3)
{
    p0[0] = p1;
    p0[1] = p2;
    p0[2] = p3;
}

void func_020ba184(UnkStruct_020ba184 *p)
{
    DC_FlushRange(p->unk_04, p->unk_08);
    GX_BeginLoadTex();
    GX_LoadTex(p->unk_04, p->unk_00, p->unk_08);
    GX_EndLoadTex();
}

void func_020ba160(unsigned int *s)
{
    DC_FlushRange((void *) s[1], s[2]);
    GX_BeginLoadTexPltt();
    GX_LoadTexPltt(s[1], s[0], s[2]);
    GX_EndLoadTexPltt();
}

void func_020ba13c(UnkStruct_020ba13c *param)
{
    ObjStruct *obj = param->ptr;
    DC_FlushRange((void *) obj, obj->unk_04);
    NNS_G3dTexLoad(obj, 1);
    NNS_G3dPlttLoad(obj, 1);
}

unsigned char func_020ba12c(void *arg0)
{
    unsigned char val;
    unsigned int val2;

    val2 = *(unsigned int *) ((unsigned char *) arg0 + 8);
    val2 = val2 >> 0xb;
    val = (unsigned char) (val2 & 0xff);
    val = (unsigned char) (val + 1);
    return val;
}

int func_020ba128(void *object)
{
    return 1;
}

unsigned char func_020ba118(void *arg0)
{
    unsigned int temp;
    unsigned char result;

    temp = *(unsigned int *) ((unsigned char *) arg0 + 8);
    temp >>= 11;
    result = (unsigned char) (temp & 0xFF);
    result = (unsigned char) (result + 1);
    return result;
}
