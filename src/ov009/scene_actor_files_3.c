/* scene_actor_files_3: 4 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02264c10 @ 0x02264c10, 0x30 bytes, Thumb
 * func_ov009_02264be0 @ 0x02264be0, 0x30 bytes, Thumb
 * func_ov009_02264b64 @ 0x02264b64, 0x7c bytes, Thumb
 * func_ov009_02264ad8 @ 0x02264ad8, 0x8c bytes, Thumb
 */

struct UnkStruct_02264c10 {
    unsigned char pad_00[0x138];
    int unk_138;
};

typedef struct {
    char pad_00[0x138];
    int unk_138;
} UnkStruct_02264be0;

struct UnkStruct_02264ad8 {
    int unk_00, unk_04, unk_08, unk_0C, unk_10, unk_14, unk_18, unk_1C;
};

extern int func_ov003_022203dc(void);
extern int func_02064328(int *a, int *b, int c, int d, int e);
extern int data_ov009_02265b54[];
extern int data_ov009_02265af0[];
extern char data_ov009_02265b74[];
extern char data_ov009_02265ad4[];
extern int func_0204bbd4(int);
extern char data_ov009_02265b94[];
extern char data_ov009_02265ab4[];
extern int func_ov009_022648e4(char *, int, int, int);
extern struct UnkStruct_02264ad8 *func_ov009_02264884(char *);
extern int func_02055f2c(void *, int, int);
extern int func_ov003_022203c8(void);
extern int func_ov003_0221fe2c(void *argument0);
extern int NNS_G3dBindMdlPltt(int, int);
extern int NNS_G3dBindMdlTex(int, int);

int *func_ov009_02264c10(struct UnkStruct_02264c10 *param)
{
    int field = param->unk_138;
    int local = func_ov003_022203dc();
    func_02064328(data_ov009_02265b54, data_ov009_02265af0, field, field, local);
    return data_ov009_02265b54;
}

char *func_ov009_02264be0(UnkStruct_02264be0 *s)
{
    int val = s->unk_138;
    func_02064328((int *) data_ov009_02265b74, (int *) data_ov009_02265ad4, (int) val, (int) val, (int) (func_ov003_022203dc()));
    return data_ov009_02265b74;
}

void *func_ov009_02264b64(char *self)
{
    volatile unsigned short t;
    int h;

    t = (unsigned short) func_0204bbd4(*(int *) (self + 0x138));
    switch (t) {
        case 0x500a:
        case 0x5011:
        case 0x501c:
        case 0x501d:
            return 0;
    }
    h = *(int *) (self + 0x138);
    func_02064328((int *) data_ov009_02265b94, (int *) data_ov009_02265ab4, h, h, func_ov003_022203dc());
    return data_ov009_02265b94;
}

int func_ov009_02264ad8(char *self, int a, int b, int c)
{
    struct UnkStruct_02264ad8 *e;
    int p;

    if (*(int *) (self + 0x284) != 0 || *(int *) (self + 0x198) != 0) {
        return 1;
    }
    func_ov009_022648e4(self, a, b, c);
    e = func_ov009_02264884(self);
    if (e == 0 || e->unk_00 == 0) {
        goto ret1b;
    }
    p = e->unk_00;
    if (func_02055f2c(self + 0x13c, p, 0) == 0) {
        goto ret0;
    }

    NNS_G3dBindMdlPltt(e->unk_00, func_ov003_0221fe2c((void *) func_ov003_022203c8()));
    if (e->unk_14 != 0) {
        NNS_G3dBindMdlTex(e->unk_00, e->unk_14);
    }
    if (e->unk_18 != 0) {
        NNS_G3dBindMdlTex(e->unk_00, e->unk_18);
        NNS_G3dBindMdlPltt(e->unk_00, e->unk_18);
    }
    return 1;
ret0:
    return 0;
ret1b:
    return 1;
}
