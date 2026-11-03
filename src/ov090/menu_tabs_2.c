/* menu_tabs_2: 4 functions, module ov090
 * mwccarm 1.2/base -O4,s
 * func_ov090_02299774 @ 0x02299774, 0x4c bytes, Thumb
 * func_ov090_0229971c @ 0x0229971c, 0x58 bytes, Thumb
 * func_ov090_022996fc @ 0x022996fc, 0x1e bytes, Thumb
 * func_ov090_02299688 @ 0x02299688, 0x74 bytes, Thumb
 */

typedef struct {
    char data[0x38];
} UnkStruct_02299774;

typedef struct {
    char pad_00;
} OtherObj;

typedef struct {
    void *vtable;
    char pad_04[0x9c - 4];
    UnkStruct_02299774 subs[3];
    char pad_144[0x1164 - 0x144];
    OtherObj other;
} Obj_ov090_02299820;

extern void *func_ov002_02207f80(unsigned int);
extern void *func_ov002_0220830c(void *);
extern void *func_020b9af4(UnkStruct_02299774 *);
extern void *func_ov002_0220ba24(OtherObj *);
extern char data_ov090_02299820[];
extern void func_0206f55c(void);
extern void func_ov090_0229915c(void *p);
extern void func_0206ef98(void);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_0206fbb4(void);
extern void func_020041fc(void);
extern void func_0206fe38(void);
extern unsigned char data_ov090_02299960;
extern void func_0206ef34(void);
extern void func_ov090_02299154(void *arg);
extern void func_020041ec(void);
extern void func_0206f54c(void);
extern unsigned char data_ov090_02299880[];
extern int func_020896b8(int a, void *p, int b, int c, int d, int e, int f);

Obj_ov090_02299820 *func_ov090_02299774(void)
{
    Obj_ov090_02299820 *obj;
    UnkStruct_02299774 *p;
    obj = (Obj_ov090_02299820 *) func_ov002_02207f80(0x1280);
    if (obj) {
        func_ov002_0220830c(obj);
        obj->vtable = data_ov090_02299820;
        p = &obj->subs[0];
        do {
            func_020b9af4(p);
            p++;
        } while (p != &obj->subs[3]);
        func_ov002_0220ba24(&obj->other);
    }
    return obj;
}

int func_ov090_0229971c(char *self)
{
    *(unsigned char *) (self + 0x98) = 1;
    func_0206f55c();
    func_ov090_0229915c(self);
    func_0206ef98();
    *(unsigned char *) (self + 0x96) = 0xff;
    data_ov090_02299960 = 0;
    *(unsigned char *) (self + 0x97) = 0;
    *(unsigned char *) (self + 0x8d) = 1;
    *(unsigned char *) (self + 0x8c) = 0;
    func_ov002_022080a0(self, 0);
    func_0206fbb4();
    func_020041fc();
    func_0206fe38();
    return 1;
}

int func_ov090_022996fc(void *arg)
{
    func_0206ef34();
    func_ov090_02299154(arg);
    func_020041ec();
    func_0206f54c();
    return 1;
}

int func_ov090_02299688(unsigned char *self)
{
    int i, j;
    int m1;
    int zeroA;
    int zeroB;

    if (self[0x91] == 0) {
        return 0;
    }

    j = 0;
    i = j;
    m1 = ~j;
    zeroA = j;
    zeroB = j;
    do {
        func_020896b8(1, &data_ov090_02299880[j * 8], 0x80, self[0x92] + 0x50, m1, 2, zeroA);
        func_020896b8(1, &data_ov090_02299880[(j + 1) * 8], 0x80, self[0x92] + 0x50, m1, 2, zeroB);
        i++;
        j += 2;
    } while (i <= 7);
    return 1;
}
