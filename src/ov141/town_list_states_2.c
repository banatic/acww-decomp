/* town_list_states_2: 11 functions, module ov141
 * mwccarm 1.2/base -O4,s
 * func_ov141_0229aba0 @ 0x0229aba0, 0x4 bytes, Thumb
 * func_ov141_0229ab9c @ 0x0229ab9c, 0x4 bytes, Thumb
 * func_ov141_0229ab28 @ 0x0229ab28, 0x74 bytes, Thumb
 * func_ov141_0229ab04 @ 0x0229ab04, 0x22 bytes, Thumb
 * func_ov141_0229aac4 @ 0x0229aac4, 0x40 bytes, Thumb
 * func_ov141_0229aa94 @ 0x0229aa94, 0x2e bytes, Thumb
 * func_ov141_0229aa54 @ 0x0229aa54, 0x3e bytes, Thumb
 * func_ov141_0229aa28 @ 0x0229aa28, 0x2a bytes, Thumb
 * func_ov141_0229aa04 @ 0x0229aa04, 0x24 bytes, Thumb
 * func_ov141_0229a9b0 @ 0x0229a9b0, 0x54 bytes, Thumb
 * func_ov141_0229a984 @ 0x0229a984, 0x2c bytes, Thumb
 */

extern int func_ov141_02299f7c(void *self, int a);
extern void func_0206fc4c(int a);
extern unsigned int *func_0206f7bc(void);
extern int func_0206f7b0(void);
extern void func_0206f7c8(void);
extern void MI_CpuCopy8(void *src, void *dst, unsigned int len);
extern void func_020ee470(void *self);
extern void func_ov141_0229a8d0(void);
extern void func_ov141_0229a850(void *);
extern void func_ov141_0229a834(void *);
extern void func_ov002_02208090(void *, int);
extern void func_ov139_022997f0(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov141_02299f6c(void *, int);
extern int func_ov002_02207f48(void *param, int arg);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov141_0229a560(void *param);
extern void func_ov141_02299fcc(void *receiver);
extern void func_ov141_02299fc8(void);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int a);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);
extern void func_ov139_02299af8(void *p, int a, int b);
extern int func_ov141_02299f94(void *p, int a);
extern void func_ov002_0220af74(void *);
extern void func_ov139_02299adc(void *);
extern void func_020b9ccc(void *);

void func_ov141_0229aa04(void *p);

int func_ov141_0229aba0(void)
{
    return 1;
}

int func_ov141_0229ab9c(void)
{
    return 1;
}

int func_ov141_0229ab28(char *self)
{
    unsigned int *p;
    int flag2;

    if (func_ov141_02299f7c(self, 2) != 0) {
        func_0206fc4c(0);
    } else {
        int idx;
        func_0206fc4c(1);

        p = func_0206f7bc();
        if (p != 0) {
            idx = *(int *) (self + 0x1270);
            MI_CpuCopy8(self + 0xc8c + idx * 0xe0, p, 0xe0);
        }

        flag2 = func_0206f7b0();
        if (flag2 != 0) {
            idx = *(int *) (self + 0x1270);
            MI_CpuCopy8(self + 0x11cc + idx * 0x1a, (void *) flag2, 0x1a);
        }
    }

    func_0206f7c8();
    func_020ee470(self);
    return 1;
}

void func_ov141_0229ab04(void *p)
{
    func_ov141_0229a8d0();
    func_ov141_0229a850(p);
    func_ov141_0229a834(p);
    func_ov002_02208090(p, 1);
}

void func_ov141_0229aac4(void *p)
{
    func_ov139_022997f0((char *) p + 0x94);
    func_ov002_02207f20(p, 8, 4, 0, 0x30);
    func_02002708(6);
    func_ov141_0229aa04(p);
    func_ov141_02299f6c(p, 1);
    func_ov002_02208090(p, 2);
}

void func_ov141_0229aa94(void *param)
{
    if (func_ov002_02207f48(param, 0)) {
        func_ov002_022080a0((void *) (param), 2);
        func_ov141_0229a560(param);
        func_ov141_02299fcc(param);
    }
    func_ov141_0229aa04(param);
}

void func_ov141_0229aa54(void *param)
{
    func_ov141_02299fc8();
    func_ov092_02299324(func_020ee45c(param), 0x44, 1);
    func_ov002_02207f04(param, 8, 0, 0, 0x30);
    func_ov141_0229aa04(param);
    func_ov002_02208090(param, 4);
}

void func_ov141_0229aa28(int param)
{
    if (func_ov002_02207f3c(param, 0)) {
        func_020027f0(6);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov141_0229aa04((void *) param);
    }
}

void func_ov141_0229aa04(void *p)
{
    func_ov002_02207e80(p, 6, 0, 0);
    *(int *) ((char *) p + 0x1268) = func_ov002_02207f60(p);
}

void func_ov141_0229a9b0(void *self)
{
    unsigned char *p;
    int i;

    *(unsigned short *) ((char *) self + 0x1a7c) = 0;
    func_ov139_02299af8((char *) self + 0x94, 6, 0x7e);

    for (i = 0; i < 6; i++) {
        *((unsigned char *) self + 0x1a7f + i) = 0;
    }

    func_ov141_02299f94(self, -1);
    *(int *) ((char *) self + 0x1278) = 8;
    *((unsigned char *) self + 0x1a8c) = 0;
}

void func_ov141_0229a984(char *self)
{
    func_ov002_0220af74(self + 0xa9c);
    func_ov139_02299adc(self + 0x94);
    func_020b9ccc(self + 0xc68);
}
