/* screen_mark_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208ef58 @ 0x0208ef58, 0x24 bytes, Thumb
 * func_0208ef34 @ 0x0208ef34, 0x24 bytes, Thumb
 * func_0208ef0c @ 0x0208ef0c, 0x28 bytes, Thumb
 * func_0208eea0 @ 0x0208eea0, 0x6c bytes, Thumb
 */

struct Func0208ef58Obj {
    void *unk_00;
    unsigned char pad_04[8];
    unsigned char sub[8];
    unsigned char pad_14[12];
    int unk_20;
};

typedef struct UnkStruct_0208ef34 {
    int *unk_00;
    char pad_04[8];
    char unk_0C[4];
} UnkStruct_0208ef34;

typedef struct {
    int pad_00;
} UnkStruct_0208eea0;

struct UnkStruct_0208eea0_2 {
    unsigned char pad_00[0x0c];
    UnkStruct_0208eea0 sub;
    unsigned char pad_10[0x10];
    int flag;
};

extern void func_0208af30(void *obj);
extern void func_0208a1f8(void *sub);
extern unsigned char data_020e236c[];
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *) __attribute__((arm));
extern int func_0208a1d0(void *ptr);
extern int func_0208aef0(void *obj);
extern int func_0208a1b0(void *ptr, int arg);
extern int func_0208aeec(void *obj);
extern int func_0208a198(void *ptr, int arg);
extern void func_02088df8(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);

void *func_0208ef58(struct Func0208ef58Obj *obj)
{
    func_0208af30(obj);
    obj->unk_00 = data_020e236c;
    func_0208a1f8(obj->sub);
    obj->unk_20 = 0;
    return obj;
}

UnkStruct_0208ef34 *func_0208ef34(UnkStruct_0208ef34 *this)
{
    this->unk_00 = ((int *) data_020e236c);
    func_0208a1f4(&this->unk_0C);
    func_0208af00(this);
    return this;
}

void *func_0208ef0c(void *arg)
{
    *(void **) arg = (void *) ((char *) data_020e236c);
    func_0208a1f4((char *) arg + 0xc);
    func_0208af00(arg);
    func_020edb3c(arg);
    return arg;
}

void func_0208eea0(struct UnkStruct_0208eea0_2 *obj)
{
    int v7, v4, v6, sum;

    UnkStruct_0208eea0 *sub;
    if (obj->flag == 0) {
        return;
    }

    v7 = func_0208a1d0(&obj->sub);
    v4 = func_0208aef0(obj);
    v4 += func_0208a1b0(&obj->sub, -1);
    v6 = func_0208aeec(obj);
    sub = &obj->sub;
    sum = v6 + func_0208a198(sub, -1);
    func_02088df8(0, v7, v4, sum, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
