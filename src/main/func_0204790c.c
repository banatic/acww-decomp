/* func_0204790c @ 0x0204790c, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_0204790c;

extern UnkStruct_0204790c *func_0203fc70(void);
extern void func_0209df7c(unsigned int *t);
extern int func_0209fa30(int v);
extern void func_02047bf8(void *a, int b, UnkStruct_0204790c *e, int c, int d, int p4, int p5, int r, int p6);
extern void func_02047a8c(void *a, int b, int c);
extern void func_020b2ec8(void);
extern void func_02047bc8(void *a, int b, UnkStruct_0204790c *e, int p4, int p5, int r, int p6);
extern void func_020479e0(void *a, unsigned short k);

void func_0204790c(void *a, int p1, int p2, int p3, int p4, int p5, int p6)
{
    unsigned int t;
    UnkStruct_0204790c *e;
    int i;
    int r;
    int ok;

    e = func_0203fc70();
    func_0209df7c(&t);
    r = func_0209fa30(p6 + 0x173dd);
    for (i = 0; i < 7; e++, i++) {
        unsigned short k = e->unk_00;
        if (k == 0x63) {
            continue;
        }
        if (e->unk_04 > t) {
            continue;
        }
        if (e->unk_08 <= t) {
            continue;
        }
        ok = 0;
        switch (k) {
            case 0x10:
                func_02047bf8(a, p1, e, p2, p3, p4, p5, r, p6);
                ok = 1;
                break;
            case 0x11:
            case 0x61:
                func_02047a8c(a, p1, p2);
                ok = 1;
                break;
            case 0x62:
                func_020b2ec8();
                ok = 1;
                break;
            case 0xe:
                func_02047bc8(a, p1, e, p4, p5, r, p6);
                ok = 1;
                break;
        }
        if (ok != 0) {
            func_020479e0(a, e->unk_00);
        }
    }
}
