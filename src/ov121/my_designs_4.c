/* my_designs_4: 5 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229a480 @ 0x0229a480, 0x8c bytes, Thumb
 * func_ov121_0229a450 @ 0x0229a450, 0x30 bytes, Thumb
 * func_ov121_0229a3fc @ 0x0229a3fc, 0x54 bytes, Thumb
 * func_ov121_0229a3a8 @ 0x0229a3a8, 0x54 bytes, Thumb
 * func_ov121_0229a37c @ 0x0229a37c, 0x2c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xAD];
    unsigned char unk_AD;
    unsigned char pad_AE[0x22A];
    unsigned char unk_2D8[1];
} UnkStruct_0229a480;

typedef struct UnkStruct_0229a3fc {
    int pad_00;
} UnkStruct_0229a3fc;

typedef struct UnkStruct_0229a3fc_2 {
    unsigned char pad_00[0x3a8];
    UnkStruct_0229a3fc sub;
} UnkStruct_0229a3fc_2;

typedef struct UnkStruct_0229a37c {
    char pad_00[0xB1];
    unsigned char byte;
} UnkStruct_0229a37c;

extern int func_ov121_0229af40(void *obj, unsigned char byte);
extern int func_ov121_0229af58(void *obj, unsigned char byte);
extern int func_0206fe54(void);
extern void func_0208aa60(void *dst, int value, int offset);
extern int func_02062e50(void *buf);
extern int func_020984e8(void);
extern void *func_020996b8(void *object);
extern int func_02072bb0(int c, unsigned char byte);
extern int func_02072d4c(int d);
extern void func_02072ea4(int e, void *buf);
extern void *func_0208aecc(void *buf);
extern int func_02051984(void *dst, void *src);
extern void func_0208aa48(void *dst, void *src);
extern void func_0208aeb8(void *buf);
extern void *func_02062e00(void *buf);
extern void func_ov002_02207cf8(void *);
extern void func_ov002_02207cf0(void *);
extern int func_ov121_02299fc8(UnkStruct_0229a3fc_2 *p);
extern void func_ov121_0229a190(UnkStruct_0229a3fc_2 *p);
extern void func_ov002_0220a0b4(UnkStruct_0229a3fc *addr, int a, int b);
extern void func_ov002_0220a374(UnkStruct_0229a3fc *addr, int val);
extern int func_ov121_02299a5c(char *self, int n);

int func_ov121_0229a3a8(char *self);
int func_ov121_0229a37c(UnkStruct_0229a37c *self);

void func_ov121_0229a480(UnkStruct_0229a480 *obj)
{
    int res1;
    int offset;
    int raw;
    int a, b, c, d, e;
    char buf1[0x24];
    char buf2[0x30];

    res1 = func_ov121_0229af40(obj, obj->unk_AD);
    offset = res1 - 0x84;
    if (func_0206fe54()) {
        offset -= 0xA;
    }

    raw = func_ov121_0229af58(obj, obj->unk_AD);
    func_0208aa60(obj->unk_2D8, raw - 0x78, offset);

    a = func_02062e50(buf1);
    b = func_020984e8();
    c = (int) func_020996b8((void *) b);
    d = func_02072bb0(c, obj->unk_AD);
    e = func_02072d4c(d);
    func_02072ea4(e, buf1);
    func_0208aecc(buf2);
    func_02051984(buf2, buf1);
    func_0208aa48(obj->unk_2D8, buf2);
    func_0208aeb8(buf2);
    func_02062e00(buf1);
}

void func_ov121_0229a450(void *self)
{
    unsigned char v;
    void *p;

    v = *(unsigned char *) ((char *) self + 0xb1);
    if (v <= 7) {
        *(unsigned char *) ((char *) self + 0xad) = v;
        p = (char *) self + 0x2d8;
        func_ov002_02207cf8(p);
    } else {
        p = (char *) self + 0x2d8;
        func_ov002_02207cf0(p);
    }
}

void func_ov121_0229a3fc(UnkStruct_0229a3fc_2 *p)
{
    int r4;
    int r2;
    int ret;
    r4 = func_ov121_0229a3a8((char *) p);
    r2 = func_ov121_0229a37c((UnkStruct_0229a37c *) p);
    func_ov002_0220a0b4(&p->sub, r4, r2);
    ret = func_ov121_02299fc8(p);
    if (ret != -1) {
        func_ov002_0220a374(&p->sub, 13);
    } else {
        func_ov002_0220a374(&p->sub, 1);
    }
    func_ov121_0229a190(p);
}

int func_ov121_0229a3a8(char *self)
{
    int result = func_ov121_0229af58((void *) self, *(unsigned char *) (self + 0xb1));
    if (func_ov121_02299a5c(self, 0x40)) {
        result += 0x100;
    } else if (func_ov121_02299a5c(self, 0x20)) {
        result -= 0x100;
    }
    if (func_ov121_02299fc8((UnkStruct_0229a3fc_2 *) self) == -1) {
        result += 0xb;
    }
    return result;
}

int func_ov121_0229a37c(UnkStruct_0229a37c *self)
{
    int r4 = func_ov121_0229af40((void *) self, self->byte);
    if (func_ov121_02299fc8((UnkStruct_0229a3fc_2 *) self) == -1) {
        r4 -= 11;
    }
    return r4;
}
