/* nook_store_4: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020afc2c @ 0x020afc2c, 0x30 bytes, Thumb
 * func_020afc10 @ 0x020afc10, 0x1c bytes, Thumb
 * func_020afbcc @ 0x020afbcc, 0x44 bytes, Thumb
 * func_020afb90 @ 0x020afb90, 0x3c bytes, Thumb
 * func_020afb48 @ 0x020afb48, 0x48 bytes, Thumb
 * func_020afb24 @ 0x020afb24, 0x22 bytes, Thumb
 * func_020afad8 @ 0x020afad8, 0x4c bytes, Thumb
 * func_020afad4 @ 0x020afad4, 0x4 bytes, Thumb
 */

typedef struct {
    char pad_00[0x52];
    unsigned char unk_52;
    unsigned char unk_53;
    unsigned char unk_54;
} UnkStruct_020afb48;

typedef struct {
    char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
} UnkStruct_020afb48_2;

extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020af880(void *);
extern void func_0209e474(unsigned int *local);
extern char data_021dc7a8;
extern int func_0209f150(void *ptr, int n);
extern int func_020af854(void *p, unsigned int i, unsigned short *c);
extern int func_0204bcdc(int x);
extern int func_0206300c(int x, int y);

void func_020afbcc(void *param);

void *func_020afc2c(void *p)
{
    __cxa_vec_ctor((void *) ((char *) p + 4), 0x25, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    func_020afbcc(p);
    return p;
}

void *func_020afc10(void *arg)
{
    __cxa_vec_cleanup((void *) ((char *) arg + 4), 0x25, 2, (void (*)(void *)) func_020051b0);
    return arg;
}

void func_020afbcc(void *param)
{
    unsigned short *p;
    unsigned char *q;
    unsigned short val;
    unsigned char *r;

    func_020af880(param);
    p = (unsigned short *) ((char *) param + 0x5a);
    val = *p;
    val &= 0xfffff9ff;
    *p = val;
    *(int *) param = 0;
    p = (unsigned short *) ((char *) param + 0x5a);
    val = *p;
    val &= ~0x1f;
    *p = val;
    q = (unsigned char *) ((char *) param + 0x51);
    *q = 1;
    r = (unsigned char *) ((char *) param + 0x59);
    *r = 0;
}

int func_020afb90(void *p)
{
    unsigned int local[2];
    unsigned int v;
    unsigned int r;
    unsigned char b;
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    v = *(unsigned short *) ((char *) p + 0x5a);
    r = v << 0x1b;
    r = r >> 0x1b;
    if (r == 0) {
        goto L0;
    }
    b = ((unsigned char *) local)[2];
    if ((int) b < (int) r) {
        goto L1;
    }
    if (b >= 0x17u) {
        goto L1;
    }
    return 1;
L1:
    return 0;
L0:
    return 0;
}

int func_020afb48(UnkStruct_020afb48 *p1, UnkStruct_020afb48_2 *p2)
{
    if (func_0209f150(&data_021dc7a8, 5) != 0) {
        if (p1->unk_54 == p2->unk_05) {
            if (p1->unk_53 == p2->unk_04) {
                if (p1->unk_52 == p2->unk_03) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int func_020afb24(void *param)
{
    void *sp[2];
    sp[0] = 0;
    sp[1] = 0;
    func_0209e474((unsigned int *) sp);
    return func_020afb48((UnkStruct_020afb48 *) param, (UnkStruct_020afb48_2 *) sp);
}

int func_020afad8(void *p)
{
    unsigned int i = 0;
    int j = i;
    for (; i < 0x25; i++) {
        unsigned short c = 0xfff1;
        int r = func_020af854(p, i, &c);
        if (func_0204bcdc(r)) {
            if (func_0206300c(r, j) == 4) {
                return 1;
            }
        }
    }
    return 0;
}

int func_020afad4(int p0)
{
    return ((int) (p0) + (86));
}
