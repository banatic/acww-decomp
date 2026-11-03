/* ab_all_obj: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02003164 @ 0x02003164, 0x8 bytes, Thumb
 * func_0200314c @ 0x0200314c, 0x16 bytes, Thumb
 * func_02003108 @ 0x02003108, 0x44 bytes, Thumb
 * func_02003100 @ 0x02003100, 0x8 bytes, Thumb
 * func_020030dc @ 0x020030dc, 0x24 bytes, Thumb
 * func_020030bc @ 0x020030bc, 0x20 bytes, Thumb
 * func_020030a4 @ 0x020030a4, 0x18 bytes, Thumb
 * func_0200308c @ 0x0200308c, 0x18 bytes, Thumb
 * func_02003064 @ 0x02003064, 0x26 bytes, Thumb
 * func_02003038 @ 0x02003038, 0x2c bytes, Thumb
 */

typedef struct {
    char pad_00[0x48];
    volatile int unk_48;
} UnkStruct_020030dc;

struct UnkStruct_020030bc {
    char pad_00[0x4c];
    int unk_4C;
};

struct UnkStruct_02003064 {
    unsigned char pad_00[0x48];
    void *unk_48;
};

extern int data_0213ff20;
extern void FS_InitFile(void *file);
extern int data_020d7220;
extern int func_02064b18(int *);
extern char data_020d7204;
extern void func_020e9898(int);
extern void DC_FlushRange(void *, int);
extern void GX_LoadOBJPltt(void *, int, int);
extern void GXS_LoadOBJPltt(void *, int, int);
extern void GX_LoadOBJ(void *param1, int param2, int param3);
extern void GXS_LoadOBJ(void *param1, int param2, int param3);

void func_02003100(void *file);
int func_020030dc(UnkStruct_020030dc *s);
int func_020030bc(struct UnkStruct_020030bc *param);
void func_020030a4(void *arg0);
void func_0200308c(void *arg0);
void func_02003064(struct UnkStruct_02003064 *p);
void func_02003038(void *param1);

void func_02003164(int *p0)
{
    p0[18] = 0;
    p0[19] = 0;
}

void *func_0200314c(void *p)
{
    func_020030a4(p);
    func_0200308c(p);
    return p;
}

void func_02003108(void)
{
    int *p = &data_0213ff20;
    int r4, r5;

    func_02003100((void *) p);
    r4 = func_020030dc((UnkStruct_020030dc *) p);
    r5 = func_020030bc((struct UnkStruct_020030bc *) p);
    if (r4 != 0) {
        func_02003064((struct UnkStruct_02003064 *) p);
    }
    if (r5 != 0) {
        func_02003038((void *) p);
    }
    func_020030a4((void *) p);
    func_0200308c((void *) p);
}

void func_02003100(void *file)
{
    FS_InitFile(file);
}

int func_020030dc(UnkStruct_020030dc *s)
{
    s->unk_48 = func_02064b18(&data_020d7220);
    if (s->unk_48) {
        return 1;
    } else {
        return 0;
    }
}

int func_020030bc(struct UnkStruct_020030bc *param)
{
    int result;
    result = func_02064b18((int *) (&data_020d7204));
    param->unk_4C = result;
    if (result) {
        return 1;
    } else {
        return 0;
    }
}

void func_020030a4(void *arg0)
{
    int condition_value0;
    void *r4 = arg0;
    if ((condition_value0 = (int) (*(unsigned int *) ((char *) r4 + 0x48))) != 0) {
        func_020e9898(condition_value0);
        *(unsigned int *) ((char *) r4 + 0x48) = 0;
    }
}

void func_0200308c(void *arg0)
{
    int condition_value0;
    if ((condition_value0 = (int) (*(unsigned int *) ((char *) arg0 + 0x4c))) != 0) {
        func_020e9898(condition_value0);
        *(unsigned int *) ((char *) arg0 + 0x4c) = 0;
    }
}

void func_02003064(struct UnkStruct_02003064 *p)
{
    DC_FlushRange(p->unk_48, 0x80);
    GX_LoadOBJPltt(p->unk_48, 0, 0x80);
    GXS_LoadOBJPltt(p->unk_48, 0, 0x80);
}

void func_02003038(void *param1)
{
    void *r4 = param1;
    DC_FlushRange(*(void **) ((char *) r4 + 0x4c), 0x1000);
    GX_LoadOBJ(*(void **) ((char *) r4 + 0x4c), 0, 0x1000);
    GXS_LoadOBJ(*(void **) ((char *) r4 + 0x4c), 0, 0x1000);
}
