/* func_ov132_0229ae4c @ 0x0229ae4c, 0x44 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a314(void *p);
extern void func_ov002_0220a2b4(void *p);
extern int func_ov132_0229aed8(void *p);
extern int func_ov132_0229aeac(void *p);
extern void func_ov132_0229ae18(void *p, int a, int b);

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
