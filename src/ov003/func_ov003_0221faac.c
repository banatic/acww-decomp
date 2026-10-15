/* func_ov003_0221faac @ 0x0221faac, 0x1f8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0221faac {
    char *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_0221faac;

extern UnkStruct_0221faac *data_021c80bc;
extern void *data_021c9b24;
extern char data_ov003_02239aac[], data_ov003_02239ab8[], data_ov003_02239ac4[], data_ov003_02239acc[];

extern void func_ov003_0221f1ec(void *p);
extern int func_ov003_0221f1ac(void *p);
extern void *func_0203750c(void);
extern int func_02037594(void *h);
extern int func_02037564(void *h);
extern int func_02037570(void *h);
extern int func_0203754c(void *h);
extern int func_02037558(void *h);
extern int func_020575e4(void *p, int a, void *b, void *c, int d, int e, int f);
extern void *func_020e9948(void *heap, int size);
extern char *func_ov003_0221f3b0(char *p);
extern void func_0204f800(int *a, int *b, int x, int z, int i, int j);
extern int func_02031478(int a, int b);
extern void func_0204f7ac(int *v, int x, int z, int i, int j);
extern int func_ov003_0221f47c(void *p, int *v, int idx);
extern int func_ov003_0221f270(char *p, char *e, int x, int y);
extern void func_ov003_0221ef70(void *p);

int func_ov003_0221faac(char *self)
{
    unsigned int z;
    unsigned int i;
    unsigned int n;
    int idx;
    int aa, bb;
    int v3[3];
    UnkStruct_0221faac *g;
    int t;
    int u;
    char *p;
    unsigned int x, j, y;
    char *e;

    func_ov003_0221f1ec(self + 0x150);
    func_ov003_0221f1ac(self + 0x150);
    t = func_02037594(func_0203750c());
    u = func_02037564(func_0203750c());
    func_020575e4(self + 0x1f0, t, data_ov003_02239aac, data_ov003_02239ab8, u, func_02037570(func_0203750c()), 0);
    t = func_02037594(func_0203750c());
    u = func_0203754c(func_0203750c());
    func_020575e4(self + 0x280, t, data_ov003_02239ac4, data_ov003_02239acc, u, func_02037558(func_0203750c()), 1);
    g = data_021c80bc;
    *(unsigned int *) (self + 0x148) = g->unk_04;
    *(unsigned int *) (self + 0x14c) = g->unk_08;
    *(int *) (self + 0x50) =
        (int) func_020e9948(data_021c9b24, 0xec * *(unsigned int *) (self + 0x148) * *(unsigned int *) (self + 0x14c));
    p = (char *) *(int *) (self + 0x50);
    while (p <
           (char *) *(int *) (self + 0x50) + (*(unsigned int *) (self + 0x148) * *(unsigned int *) (self + 0x14c) * 0xec)) {
        if (p != 0) {
            p = func_ov003_0221f3b0(p);
        }
        p = p + 0xec;
    }
    for (z = 0; z < *(unsigned int *) (self + 0x14c); z++) {
        for (x = 0; x < *(unsigned int *) (self + 0x148); x++) {
            for (j = 0; j < 0x10; j++) {
                for (i = 0; i < 0x10; i++) {
                    func_0204f800(&aa, &bb, x, z, i, j);
                    idx = func_02031478(aa, bb);
                    if (idx != -1) {
                        v3[0] = 0;
                        v3[1] = 0;
                        v3[2] = 0;
                        func_0204f7ac(v3, x, z, i, j);
                        func_ov003_0221f47c(self + 0x54, v3, idx);
                    }
                }
            }
        }
    }
    n = 0;
    for (y = 0; y < *(unsigned int *) (self + 0x14c); y++) {
        for (x = 0; x < *(unsigned int *) (self + 0x148); x++) {
            if (x < g->unk_04 && y < g->unk_08 && g->unk_00 != 0) {
                e = g->unk_00 + 0x28 * (x + y * g->unk_04);
            } else {
                e = 0;
            }
            func_ov003_0221f270((char *) *(int *) (self + 0x50) + 0xec * n++, e, x, y);
        }
    }
    func_ov003_0221ef70(self + 0x310);
    return 1;
}
