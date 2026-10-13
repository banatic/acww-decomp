/* func_020a636c @ 0x020a636c, 0x318 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a636c_2;

struct UnkStruct_020a636c {
    char pad_00[0x64];
    int unk_64;
};

extern struct UnkStruct_020a636c *data_020ccf94;
extern unsigned short data_020e3c80;

extern int func_020a6684(struct UnkStruct_020a636c_2 *o);
extern void func_020a6f88(void);
extern void func_020a6340(struct UnkStruct_020a636c_2 *o);
extern void func_020a6248(struct UnkStruct_020a636c_2 *o, int a);
extern void func_020a6eb0(int a);
extern int func_020a72d0(int a);
extern void func_020a6688(struct UnkStruct_020a636c_2 *o, int a);
extern int func_020a7450(void);
extern int func_020a744c(void);
extern void func_020a6e4c(int a, unsigned char *p, unsigned char *q, unsigned char *r);
extern int func_02073dd4(struct UnkStruct_020a636c *g, int a);
extern int func_020a7330(int a);
extern void func_020a6368(struct UnkStruct_020a636c_2 *o, int a);
extern int func_020b65c4(void);
extern int func_020a6c98(int a);
extern int func_020a6354(struct UnkStruct_020a636c_2 *o, int a);
extern int func_02073690(struct UnkStruct_020a636c *g);
extern int func_0207356c(struct UnkStruct_020a636c *g);
extern int func_020734a4(struct UnkStruct_020a636c *g);
extern void func_02073410(struct UnkStruct_020a636c *g);
extern int func_020a6240(struct UnkStruct_020a636c_2 *o);
extern int func_020a6364(struct UnkStruct_020a636c_2 *o);
extern int func_020a7300(int a);
extern int func_020b5e70(void);
extern void func_020a6290(struct UnkStruct_020a636c_2 *o, int a);
extern void func_020a6694(struct UnkStruct_020a636c_2 *o, int a);
extern void func_020733ac(struct UnkStruct_020a636c *g);
extern void func_02073820(struct UnkStruct_020a636c *g);
extern int func_020a628c(struct UnkStruct_020a636c_2 *o);
extern void func_02073770(struct UnkStruct_020a636c *g, int a, int b);
extern int func_02073394(struct UnkStruct_020a636c *g);
extern void func_020a7380(int a, int b);
extern int func_020a7258(void);

void func_020a636c(struct UnkStruct_020a636c_2 *self)
{
    int sel1;
    int ok;
    int v;
    int sel2;
    int tmp;
    unsigned char a[3];
    unsigned char b[3];
    int j;
    int n;
    struct UnkStruct_020a636c *g;
    struct UnkStruct_020a636c *h;

    g = data_020ccf94;
    n = g->unk_64;

    switch (func_020a6684(self)) {
        case 16:
            if (data_020e3c80 != 5) {
                return;
            }
            func_020a6f88();
            func_020a6340(self);
            func_020a6248(self, 0);
            func_020a6eb0(0);
            return;

        case 0:
            if (!func_020a72d0(n)) {
                return;
            }
            func_020a6688(self, 1);
            return;

        case 1:
            if (func_020a7450()) {
                return;
            }
            if (func_020a744c()) {
                return;
            }
            func_020a6e4c(n, &a[0], &a[1], &a[2]);
            if (a[1]) {
                sel1 = 4;
                for (j = 0; j < 4; j++) {
                    if (j != n && func_02073dd4(g, j) && func_020a7330(j) == a[0]) {
                        sel1 = j;
                        break;
                    }
                }
                if (sel1 < 4) {
                    func_020a6368(self, sel1);
                    func_020a6688(self, 2);
                } else {
                    func_020a6368(self, 4);
                    func_020a6688(self, 5);
                }
            } else {
                func_020a6368(self, 4);
                func_020a6688(self, 4);
            }
            return;

        case 2:
            ok = 1;
            if (!func_020a6c98(func_020b65c4())) {
                for (j = 3; j >= 0; j--) {
                    if (j == n) {
                        continue;
                    }
                    if (!func_02073dd4(g, j)) {
                        continue;
                    }
                    tmp = func_020a7330(j);
                    if (tmp != func_020b65c4()) {
                        continue;
                    }
                    if (func_020a6354(self, j)) {
                        continue;
                    }
                    ok = 0;
                    break;
                }
            }
            if (!ok) {
                return;
            }
            if (func_02073690(g)) {
                return;
            }
            if (func_0207356c(g)) {
                return;
            }
            if (func_020734a4(g)) {
                return;
            }
            if (func_020a744c()) {
                return;
            }
            func_020a6340(self);
            func_02073410(g);
            func_020a6688(self, 3);
            return;

        case 4:
            if (!func_020a6240(self) && !func_020a6c98(func_020b65c4())) {
                return;
            }
            func_020a6248(self, 0);
            func_020a6688(self, 5);
            return;

        case 8:
            // != 4 with the equal case in the else branch.
            if (func_020a6364(self) != 4) {
                if (!func_020a7300(func_020a6364(self)) && !func_020a6c98(func_020b65c4())) {
                    return;
                }
                func_020a6688(self, 9);
            } else {
                func_020a6688(self, 9);
            }
            return;

        case 9:
            v = func_020b5e70();
            sel2 = 4;
            for (j = 3; j >= 0; j--) {
                if (j == n) {
                    continue;
                }
                if (!func_02073dd4(g, j)) {
                    continue;
                }
                func_020a6e4c(j, &b[0], &b[1], &b[2]);
                if (b[0] == v && b[1]) {
                    sel2 = j;
                    break;
                }
            }
            if (sel2 < 4) {
                func_020a6290(self, sel2);
                func_020a6694(self, 0);
                func_020733ac(g);
                if (!func_020a6c98(func_020b5e70())) {
                    h = data_020ccf94;
                    func_02073820(h);
                    func_02073770(h, 0xe, func_020a628c(self));
                }
                func_020a6688(self, 0xa);
            } else {
                func_020a6290(self, 4);
                func_020a6694(self, 1);
                func_020a6688(self, 0xb);
            }
            return;

        case 10:
            if (!func_02073394(g) && !func_020a6c98(func_020b5e70())) {
                return;
            }
            func_020a6688(self, 0xb);
            return;

        case 14:
            func_020a7380(g->unk_64, 1);
            func_020a6688(self, 0xf);
            return;

        case 15:
            if (func_020a7258()) {
                return;
            }
            func_020a6688(self, 0x10);
            return;
    }
}
