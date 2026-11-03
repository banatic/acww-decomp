/* snowman_3: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221a228 @ 0x0221a228, 0x1c bytes, Thumb
 * func_ov003_0221a1dc @ 0x0221a1dc, 0x4c bytes, Thumb
 * func_ov003_0221a190 @ 0x0221a190, 0x4c bytes, Thumb
 * func_ov003_0221a128 @ 0x0221a128, 0x68 bytes, Thumb
 * func_ov003_0221a0d4 @ 0x0221a0d4, 0x54 bytes, Thumb
 * func_ov003_0221a090 @ 0x0221a090, 0x44 bytes, Thumb
 */

struct UnkStruct_0221a190 {
    unsigned char pad_00[0x2f8];
    unsigned int unk_2F8;
    unsigned int unk_2FC;
    unsigned int unk_300;
    unsigned int unk_304;
    unsigned char pad_308[0x70];
    unsigned short unk_378;
};

typedef struct {
    char pad_00[0x26C];
    int unk_26C;
    int unk_270;
    char pad_274[0x30];
    char unk_2A4;
    char pad_2A5[0x3B];
    unsigned char unk_2E0;
    char pad_2E1[0x97];
    unsigned short unk_378;
} UnkStruct_0221a128;

struct func_ov003_0221a090_data {
    char pad_00[0x378];
    unsigned short flags;
};

extern void *func_0208a020(void *arg);
extern int func_ov003_0221abf8(void *object, int flag);
extern unsigned int data_020d1a10[4];
extern int func_0203e0a8(UnkStruct_0221a128 *, int);
extern void func_0203edd0(char *a);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_020ea990(char *a, char *b);
extern int func_ov003_0221a004(void *, int);

int func_ov003_0221a228(void *base)
{
    unsigned short *p = (unsigned short *) ((char *) base + 0x378);
    unsigned short v;

    v = *p;
    v &= ~0x10;
    *p = v;

    v = *p;
    v |= 0x20;
    *p = v;

    return 1;
}

void func_ov003_0221a1dc(void *s)
{
    *(unsigned int *) ((char *) s + 0x270) = *(unsigned int *) ((char *) s + 0x26c);
    if (*(unsigned char *) ((char *) s + 0x2e0) != 0) {
        void *ret;
        ret = func_0208a020((char *) s + 0x2a4);
        if (ret != 0) {
            if (*(int *) ((char *) ret + 0x98) > 0x666) {
                func_ov003_0221abf8(s, 1);
            }
        }
    }
}

int func_ov003_0221a190(struct UnkStruct_0221a190 *self)
{
    self->unk_378 &= ~0x10;
    self->unk_378 |= 0x20;
    self->unk_2F8 = data_020d1a10[0];
    self->unk_2FC = data_020d1a10[1];
    self->unk_300 = data_020d1a10[2];
    self->unk_304 = data_020d1a10[3];
    return 1;
}

void func_ov003_0221a128(UnkStruct_0221a128 *self)
{
    self->unk_270 = self->unk_26C;
    if (self->unk_2E0 != 0) {
        int ret = (int) func_0208a020((void *) (&self->unk_2A4));
        if (ret != 0 && *(int *) ((char *) ret + 0x98) > 0x666) {
            func_ov003_0221abf8(self, 1);
            return;
        }
    }
    if ((((unsigned int) self->unk_378 << 23) >> 31) != 0) {
        func_0203e0a8(self, 0);
    }
}

int func_ov003_0221a0d4(char *a, char *b)
{
    int v;
    func_0203edd0(a);
    v = FX_MulFunc(0x2000, FX_Div(0x7d000, 0x64000));
    if (b != 0 && func_020ea990(b + 0x5c, a + 0x5c) < v && *(int *) (a + 0x39c) == 0xb) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov003_0221a090(struct func_ov003_0221a090_data *param0, int action)
{
    switch (action) {
        case 0:
            func_ov003_0221a004(param0, 1);
            break;
        case 1:
            func_ov003_0221a004(param0, 1);
            param0->flags &= ~0x100;
            break;
        case 8:
            func_ov003_0221a004(param0, 0);
            break;
    }
}
