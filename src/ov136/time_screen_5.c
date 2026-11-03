/* time_screen_5: 4 functions, module ov136
 * mwccarm 1.2/base -O4,s
 * func_ov136_0229d3d4 @ 0x0229d3d4, 0x44 bytes, Thumb
 * func_ov136_0229d3b4 @ 0x0229d3b4, 0x1e bytes, Thumb
 * func_ov136_0229d398 @ 0x0229d398, 0x1a bytes, Thumb
 * func_ov136_0229d344 @ 0x0229d344, 0x54 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char flag;
} UnkStruct_0229d3b4;

typedef struct {
    char pad_00[0x94];
    char unk_94[0x64];
    char unk_F8[0x1CC];
    char unk_2C4;
} UnkStruct_0229d344;

extern void *func_ov002_02207f80(int size);
extern void *func_ov002_0220830c(void *obj);
extern void *func_ov002_02209ccc(void *obj);
extern void *func_ov002_0220b008(void *obj);
extern void *func_ov134_0229bed4(void *obj);
extern unsigned char data_ov136_0229d510;
extern void func_ov136_0229d00c(UnkStruct_0229d3b4 *self);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);
extern int func_020ee45c(void *);
extern void func_ov092_0229929c(void *argument0);
extern void func_ov136_0229cfec(void *);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *field);
extern int func_ov136_0229c574(void *self, int arg);
extern int func_ov002_02207f60(void *self);
extern void func_ov134_0229b220(void *field, int a, int b);
extern void func_ov002_0220ad18(void *field, int a);

void *func_ov136_0229d3d4(void)
{
    void *obj;
    obj = func_ov002_02207f80(0x2b78);
    if (obj) {
        func_ov002_0220830c(obj);
        *(void **) obj = &data_ov136_0229d510;
        func_ov002_02209ccc((char *) obj + 0x94);
        func_ov002_0220b008((char *) obj + 0xf8);
        func_ov134_0229bed4((char *) obj + 0x2c4);
    }
    return obj;
}

int func_ov136_0229d3b4(UnkStruct_0229d3b4 *self)
{
    func_ov136_0229d00c(self);
    self->flag = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}

int func_ov136_0229d398(void *arg)
{

    func_ov092_0229929c((void *) func_020ee45c(arg));
    func_ov136_0229cfec(arg);
    return 1;
}

int func_ov136_0229d344(UnkStruct_0229d344 *self)
{
    if (func_0206fe54()) {
        func_ov002_02209eb8(&self->unk_94);
    }
    if (func_ov136_0229c574(self, 1) == 0) {
        return 0;
    }
    func_ov134_0229b220(&self->unk_2C4, 0, func_ov002_02207f60(self));
    func_ov002_0220ad18(&self->unk_F8, func_ov002_02207f60(self));
    return 1;
}
