/* letter_storage_2: 6 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229cf48 @ 0x0229cf48, 0x78 bytes, Thumb
 * func_ov105_0229cf10 @ 0x0229cf10, 0x38 bytes, Thumb
 * func_ov105_0229cebc @ 0x0229cebc, 0x54 bytes, Thumb
 * func_ov105_0229ce54 @ 0x0229ce54, 0x68 bytes, Thumb
 * func_ov105_0229cdf0 @ 0x0229cdf0, 0x64 bytes, Thumb
 * func_ov105_0229cdbc @ 0x0229cdbc, 0x34 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x22f];
    unsigned char unk_2BD;
    unsigned char pad_2BE[0x24a4 - 0x2bd - 1];
    unsigned char data[1];
} UnkStruct_0229cf10;

typedef struct {
    char pad_00[0x2be];
    unsigned char unk_2BE;
    unsigned char unk_2BF;
    char pad_2C0[0x21e4];
    char thing_24a4[0x64];
    char buf_2508[1];
} UnkStruct_0229ce54;

typedef struct {
    unsigned char pad_00[0x2bf];
    unsigned char unk_2BF;
    unsigned char pad_2C0[0x21e4];
    unsigned char sub2[1];
    unsigned char pad_24A5[0x63];
    unsigned char sub1[1];
} UnkStruct_0229cdf0;

typedef struct UnkStruct_0229cdbc {
    char pad_00[0x24a4];
    int unk_24A4;
} UnkStruct_0229cdbc;

extern int func_ov105_0229c340(void *obj, int arg);
extern int func_ov105_0229cff4(void *obj);
extern int func_ov105_0229cfe4(void *obj);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov105_0229c320(void *obj, int arg);
extern void func_ov002_0220a05c(void *ptr, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *obj, unsigned char value);
extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern int func_ov002_0220a08c(void *p, int a, int b, int c);
extern int func_ov002_022090e4(void *, int);
extern void func_0208e4c0(void *, int);
extern void func_ov002_0220a374(void *p, int);

void func_ov105_0229cf48(void *obj)
{
    int a, b;
    unsigned char *src;

    if (func_ov105_0229c340(obj, 8) != 0) {
        a = func_ov105_0229cff4(obj);
        b = func_ov105_0229cfe4(obj);
        func_ov002_0220a0b4((char *) obj + 0x24a4, a, b);
        func_ov105_0229c320(obj, 8);
    } else {
        a = func_ov105_0229cff4(obj);
        b = func_ov105_0229cfe4(obj);
        func_ov002_0220a05c((char *) obj + 0x24a4, a, b, 3, 1);
        src = (unsigned char *) obj + 0x8d;
        ((unsigned char *) obj)[0x2bd] = *src;
        func_ov002_02208098(obj, 13);
    }
}

void func_ov105_0229cf10(UnkStruct_0229cf10 *self, int a, int b)
{
    func_ov002_0220a05c(&self->data[0], a, b, 3, 1);
    self->unk_2BD = self->unk_8D;
    func_ov002_02208098(self, 0xd);
}

void func_ov105_0229cebc(void *p)
{
    int v1 = func_ov002_02208ae4((char *) ((unsigned int) p + 0x2508));
    int v2 = func_ov002_02208ad8((char *) p + 0x2508, ((unsigned char *) p)[0x2bf]);
    func_ov002_0220a08c((char *) p + 0x24a4, v1, v2, 2);
    ((unsigned char *) p)[0x2bd] = ((unsigned char *) p)[0x8d];
    func_ov002_02208098(p, 13);
}

void func_ov105_0229ce54(UnkStruct_0229ce54 *this)
{
    int a, b;
    this->unk_2BE = 4;
    this->unk_2BF = func_ov002_022090e4(this->buf_2508, 1);
    a = func_ov002_02208ae4(this->buf_2508);
    b = func_ov002_02208ad8(this->buf_2508, this->unk_2BF);
    func_ov002_0220a0b4(this->thing_24a4, a, b);
    func_0208e4c0(this->thing_24a4, 8);
    func_ov002_02208098(this, 0x17);
}

void func_ov105_0229cdf0(UnkStruct_0229cdf0 *self)
{
    int r4;
    int r2;

    if (func_ov105_0229c340(self, 0x800)) {
        self->unk_2BF = 1;
    } else {
        self->unk_2BF = 0;
    }
    r4 = func_ov002_02208ae4(&self->sub1);
    r2 = func_ov002_02208ad8(&self->sub1, self->unk_2BF);
    func_ov002_0220a0b4(&self->sub2, r4, r2);
    func_ov002_0220a374(&self->sub2, 7);
}

void func_ov105_0229cdbc(UnkStruct_0229cdbc *self)
{
    int a;
    int b;
    a = func_ov105_0229cff4((void *) self);
    b = func_ov105_0229cfe4((void *) self);
    func_ov002_0220a0b4(&self->unk_24A4, a, b);
    func_ov002_0220a374(&self->unk_24A4, 1);
}
