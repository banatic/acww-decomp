/* func_ov132_0229af04 @ 0x0229af04, 0x50 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x94];
    char sub;
    char pad_95[0x146D];
    unsigned char flag;
} UnkStruct_0229af04;

extern int func_ov132_0229aed8(void *p);
extern int func_ov132_0229aeac(void *p);
extern void func_ov132_0229adfc(void *p);
extern void func_ov002_0220a0b4(void *addr, int a, int b);
extern void func_ov002_0220a374(void *addr, int val);

void func_ov132_0229af04(UnkStruct_0229af04 *p)
{
    int a = func_ov132_0229aed8(p);
    int b = func_ov132_0229aeac(p);
    func_ov002_0220a0b4(&p->sub, a, b);
    if (p->flag == 2) {
        func_ov002_0220a374(&p->sub, 7);
    } else {
        func_ov002_0220a374(&p->sub, 1);
    }
    func_ov132_0229adfc(p);
}
