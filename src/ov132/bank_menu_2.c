/* bank_menu_2: 2 functions, module ov132
 * mwccarm 1.2/base -O4,s
 * func_ov132_0229ae4c @ 0x0229ae4c, 0x44 bytes, Thumb
 * func_ov132_0229ae18 @ 0x0229ae18, 0x34 bytes, Thumb
 */

extern void func_ov002_0220a314(void *p);
extern void func_ov002_0220a2b4(void *p);
extern int func_ov132_0229aed8(void *p);
extern int func_ov132_0229aeac(void *p);
extern void func_ov002_0220a05c(void *a, int b, int c, int d, int e);
extern unsigned char *func_ov002_02208098(void *a, unsigned char value);

void func_ov132_0229ae18(void *self, int p1, int p2);

void func_ov132_0229ae4c(void *p)
{
    int v1, v2;

    if (*(unsigned char *) ((char *) p + 0x1502) == 2) {
        func_ov002_0220a314((char *) p + 0x94);
    } else {
        func_ov002_0220a2b4((char *) p + 0x94);
    }

    v1 = func_ov132_0229aed8(p);
    v2 = func_ov132_0229aeac(p);
    func_ov132_0229ae18(p, v1, v2);
}

void func_ov132_0229ae18(void *self, int p1, int p2)
{
    func_ov002_0220a05c((char *) self + 0x94, p1, p2, 3, 1);
    *((unsigned char *) ((char *) self + 0x1503)) = *((unsigned char *) ((char *) self + 0x8d));
    func_ov002_02208098(self, 2);
}
