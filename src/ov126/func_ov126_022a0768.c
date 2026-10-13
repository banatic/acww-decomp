/* func_ov126_022a0768 @ 0x022a0768, 0x80 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088bc(void *p);
extern int func_02051c8c_unk(void *base, unsigned char value);
extern void func_ov126_022a0924(void *self, unsigned char value);

int func_ov126_022a0768(unsigned char *self, void *p)
{
    unsigned char idx;

    if (p == 0) {
        return 0;
    }
    idx = self[0xa8];
    if (func_ov002_022088ac(p)) {
        if (idx != 0) {
            func_ov126_022a0924(self, (unsigned char) (idx - 1));
            return 1;
        }
        return 3;
    }
    if (func_ov002_0220889c(p)) {
        int limit;

        limit = func_02051c8c_unk(self + 0x4248, self[0xa6]);
        if (idx + 1 <= limit) {
            func_ov126_022a0924(self, (unsigned char) (idx + 1));
            return 1;
        }
        return 4;
    }
    if (func_ov002_022088bc(p)) {
        return 2;
    }
    return 0;
}
