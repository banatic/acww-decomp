/* func_0204695c @ 0x0204695c, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void);
extern void func_02046680(void);
extern char *func_020466d8(void);
extern unsigned short *func_0204f5e0(int, int, int, int, int, int);
extern void func_0204f800(char *, char *, int, int, int, int);

struct UnkStruct_0204695c {
    int pad_00;
    int unk_04;
};

void func_0204695c(void)
{
    struct UnkStruct_0204695c *obj;
    char *p;
    int bound;
    int j, i, k;
    int zero = 0;
    unsigned short *q;

    obj = (struct UnkStruct_0204695c *) func_0204e414();
    func_02046680();
    if (obj != 0) {
        bound = obj->unk_04 - 2;
        p = func_020466d8();
        for (i = 0; i < 2; i++) {
            for (j = 0; j < bound; j++) {
                q = func_0204f5e0((int) obj, j + 1, i + 1, zero, zero, zero);
                for (k = 0; k < 256; k++) {
                    if (*q == 0x6d) {
                        func_0204f800(p, p + 4, j + 1, i + 1, k % 16, k / 16);
                        p += 8;
                    }
                    q++;
                }
            }
        }
    }
}
