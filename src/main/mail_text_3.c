/* mail_text_3: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203da8c @ 0x0203da8c, 0x6 bytes, Thumb
 * func_0203da84 @ 0x0203da84, 0x6 bytes, Thumb
 * func_0203da7c @ 0x0203da7c, 0x8 bytes, Thumb
 * func_0203da78 @ 0x0203da78, 0x2 bytes, Thumb
 * func_0203d9f4 @ 0x0203d9f4, 0x84 bytes, Thumb
 * func_0203d9f0 @ 0x0203d9f0, 0x2 bytes, Thumb
 * func_0203d930 @ 0x0203d930, 0xc0 bytes, Thumb
 * func_0203d834 @ 0x0203d834, 0xfc bytes, Thumb
 * func_0203d7d8 @ 0x0203d7d8, 0x5c bytes, Thumb
 * func_0203d7c4 @ 0x0203d7c4, 0x14 bytes, Thumb
 * func_0203d7b0 @ 0x0203d7b0, 0x14 bytes, Thumb
 * func_0203d79c @ 0x0203d79c, 0x14 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[76];
    unsigned long unk_4C;
} UnkStruct_0203da8c;

typedef struct {
    unsigned char pad_00[76];
    unsigned long unk_4C;
} UnkStruct_0203da84;

typedef struct {
    char pad_00[0x24];
    void *unk_24;
    char unk_28;
} UnkStruct_0203d9f4;

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x34 - 0x1f];
} LocalT;

typedef struct {
    char pad_00[0x5c];
} Entry;

typedef struct {
    unsigned char data[0x5c];
} UnkStruct_0203d7b0;

extern void func_020a873c(void *a, void *b);
extern int func_02050bf8(unsigned char c);
extern int func_02050c04(unsigned char c);
extern void func_020a9334(void *self, int value);
extern void func_0203d4cc(LocalT *self, void *a);
extern void func_0203d4c8(LocalT *self, void *d);
extern void *func_0203d540(void *t);
extern void func_0203d4d4(void *t, int v);
extern void func_020a8164(void *t, void *p);
extern void func_0203d4d0(void *t, int v);
extern void func_0203d668(void *g);
extern int func_0203d564(void *g, void *t);
extern void *func_0203d528(void *t);
extern unsigned char data_021c69b4[];
extern Entry data_021c6ec4[];
extern int func_020a8bb8(Entry *entry, int arg);
extern int func_020b44bc(UnkStruct_0203d7b0 *ptr, int a);
extern int func_020b44a4(Entry *entry, int arg);

void func_0203da8c(UnkStruct_0203da8c *p)
{
    p->unk_4C = 1;
}

void func_0203da84(UnkStruct_0203da84 *p)
{
    p->unk_4C = 2;
}

void func_0203da7c(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (69))) + (0)) = 1;
}

void func_0203da78(void) {}

void func_0203d9f4(UnkStruct_0203d9f4 *self)
{
    unsigned char local;
    char *base;
    int first;
    int second;
    int rem;
    int result;

    func_020a873c((char *) self + 0x28, &local);
    local--;
    base = (char *) self->unk_24;
    first = *(int *) (base + 0x308);
    second = *(int *) (base + 0x304);
    if (second == 0) {
        goto simple;
    }
    rem = (second - 0xac00) % 0x1c;
    if (rem == 0) {
        goto simple;
    }
    if (first != 1) {
        goto f2b;
    }
    if (local != 6) {
        goto f2a;
    }
    if (rem != 8) {
        goto f2a;
    }
    result = func_02050bf8(local);
    goto done;
f2a:
    result = func_02050c04(local);
    goto done;
f2b:
    result = func_02050c04(local);
    goto done;
simple:
    result = func_02050bf8(local);
    goto done;
done:
    func_020a9334(self, result);
}

void func_0203d9f0(void *self, char *entry) {}

int func_0203d930(void *p0, void *p1, void *p2, void *p3, const unsigned char *p4, int p5)
{
    LocalT local;
    int v1, v2, v3;
    int result;

    func_0203d540((void *) (&local));
    func_0203d4d4((void *) (&local), 0);
    func_020a8164((void *) (&local), (void *) p5);
    local.unk_1E = *p4;

    func_0203d4cc(&local, p0);
    func_0203d4c8(&local, p3);
    func_0203d4d0((void *) (&local), 1);
    func_0203d668((void *) (((int *) data_021c69b4)));
    v1 = func_0203d564((void *) (((int *) data_021c69b4)), (void *) (&local));

    func_0203d4c8(&local, 0);
    func_0203d4cc(&local, p1);
    func_0203d4d0((void *) (&local), 2);
    func_0203d668((void *) (((int *) data_021c69b4)));
    v2 = func_0203d564((void *) (((int *) data_021c69b4)), (void *) (&local));

    func_0203d4cc(&local, p2);
    func_0203d4d0((void *) (&local), 3);
    func_0203d668((void *) (((int *) data_021c69b4)));
    v3 = func_0203d564((void *) (((int *) data_021c69b4)), (void *) (&local));

    result = (v1 && v2 && v3) ? 1 : 0;

    func_0203d528((void *) (&local));
    return result;
}

int func_0203d834(int a, int b, int c, int d, unsigned char *pe, unsigned char *pf, unsigned char *pg, unsigned char *ph,
                  void *pi)
{
    unsigned char buf[0x34];
    int r1, r2, r3, r4, ok;

    func_0203d540(buf);
    func_0203d4d4(buf, 1);
    func_020a8164(buf, pi);

    func_0203d4cc((LocalT *) buf, (void *) a);
    func_0203d4c8((LocalT *) buf, (void *) d);
    buf[0x1e] = *pe;
    func_0203d4d0(buf, 4);
    func_0203d668(((int *) data_021c69b4));
    r1 = func_0203d564(((int *) data_021c69b4), buf);

    func_0203d4c8((LocalT *) buf, 0);
    func_0203d4cc((LocalT *) buf, (void *) b);
    buf[0x1e] = *pf;
    func_0203d4d0(buf, 5);
    func_0203d668(((int *) data_021c69b4));
    r2 = func_0203d564(((int *) data_021c69b4), buf);

    func_0203d4cc((LocalT *) buf, (void *) b);
    buf[0x1e] = *pg;
    func_0203d4d0(buf, 6);
    func_0203d668(((int *) data_021c69b4));
    r3 = func_0203d564(((int *) data_021c69b4), buf);

    func_0203d4cc((LocalT *) buf, (void *) c);
    buf[0x1e] = *ph;
    func_0203d4d0(buf, 7);
    func_0203d668(((int *) data_021c69b4));
    r4 = func_0203d564(((int *) data_021c69b4), buf);

    ok = r1 && r2 && r3 && r4;
    func_0203d528(buf);
    return ok;
}

int func_0203d7d8(void *a, unsigned char *b, void *c)
{
    struct {
        unsigned char pad[0x1e];
        unsigned char x;
        unsigned char pad2[0x11];
    } buf;
    int ret;

    func_0203d540(&buf);
    func_0203d4d4(&buf, 2);
    func_020a8164(&buf, c);
    func_0203d4cc((LocalT *) (&buf), a);
    buf.x = *b;
    func_0203d4d0(&buf, 0);
    func_0203d668((void *) data_021c69b4);
    ret = func_0203d564((void *) data_021c69b4, &buf);
    func_0203d528(&buf);
    return ret;
}

int func_0203d7c4(int index, int arg)
{
    return func_020a8bb8(&data_021c6ec4[index], arg);
}

int func_0203d7b0(int index, int arg1)
{
    return func_020b44bc(&((UnkStruct_0203d7b0 *) data_021c6ec4)[index], arg1);
}

int func_0203d79c(int index, int arg)
{
    return func_020b44a4(&data_021c6ec4[index], arg);
}
