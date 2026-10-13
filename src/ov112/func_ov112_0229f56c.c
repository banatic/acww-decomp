/* func_ov112_0229f56c @ 0x0229f56c, 0xc2 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov112_0229f630(void *self, unsigned char val);
extern unsigned char func_ov112_0229f84c(void *self, int n, int *out);
extern void func_ov112_0229f6d4(void *self, unsigned char val);
extern int func_02051c8c_unk(int *ptr, int n);
extern int func_ov002_022088cc(int p);
extern int func_ov002_022088bc(int p);
extern int func_ov002_022088ac(int p);
extern int func_ov002_0220889c(int p);

struct UnkStruct_0229f56c {
    unsigned char pad_00[0x94];
    int unk_94;
    int unk_98;
    unsigned char pad_9C[0xbd - 0x9c];
    unsigned char unk_BD;
    unsigned char pad_BE[0xc0 - 0xbe];
    unsigned char unk_C0;
    unsigned char pad_C1[0xc4 - 0xc1];
    int unk_C4;
};

int func_ov112_0229f56c(struct UnkStruct_0229f56c *self, int param1)
{
    unsigned char cur;
    int n;
    int saved;
    int limit2;

    if (param1 == 0) {
        return 0;
    }

    cur = self->unk_BD;
    n = func_ov112_0229f630(self, cur);
    saved = n;

    if (func_ov002_022088cc(param1) != 0) {
        if (n > 1) {
            n--;
        }
    } else if (func_ov002_022088bc(param1) != 0) {
        n++;
        if (n > self->unk_94 || n >= 6) {
            n--;
        }
    }

    limit2 = self->unk_98;
    if (n != saved) {
        cur = func_ov112_0229f84c(self, n, &limit2);
    }

    if (func_ov002_022088ac(param1) != 0) {
        if (cur > self->unk_C0) {
            cur--;
        }
    } else if (func_ov002_0220889c(param1) != 0) {
        int maxval = func_02051c8c_unk(&self->unk_C4, 0x60);
        if (cur + 1 <= maxval) {
            cur++;
        }
    }

    if (cur == self->unk_BD) {
        return 0;
    }

    func_ov112_0229f6d4(self, cur);
    return 1;
}