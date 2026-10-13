/* func_ov129_0229c8ec @ 0x0229c8ec, 0x118 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c8ec {
    char pad_00[0xaf];
    unsigned char unk_AF;
};

struct UnkStruct_0229c8ec_2 {
    unsigned short unk_00;
    unsigned short unk_02;
};

extern struct UnkStruct_0229c8ec_2 data_021fbe40;

extern int func_ov002_02208014(struct UnkStruct_0229c8ec *self);
extern void func_ov129_0229d3e0(struct UnkStruct_0229c8ec *self);
extern void func_ov002_0220a1dc(void *ptr);
extern void func_ov002_02208098(struct UnkStruct_0229c8ec *self, int x);
extern void func_ov129_0229c3f4(struct UnkStruct_0229c8ec *self);
extern void func_ov129_0229c644(struct UnkStruct_0229c8ec *self);
extern void func_ov129_0229c684(struct UnkStruct_0229c8ec *self);
extern void *func_ov002_02208008(struct UnkStruct_0229c8ec *self);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_0220a768(void *ptr, int val);
extern int func_ov002_0220a72c(void *ptr, int val);
extern void func_ov129_0229c368(struct UnkStruct_0229c8ec *self, int a, int b);

void func_ov129_0229c8ec(struct UnkStruct_0229c8ec *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov129_0229d3e0(self);
        return;
    }
    {
        unsigned short flags = data_021fbe40.unk_02;
        if ((flags & 1) != 0) {
            func_ov002_0220a1dc((char *) self + 0x3a0);
            func_ov002_02208098(self, 0xd);
            return;
        }
        if ((flags & 2) != 0) {
            func_ov129_0229c3f4(self);
            func_ov129_0229c644(self);
            return;
        }
        if ((flags & 8) != 0) {
            func_ov129_0229c3f4(self);
            func_ov129_0229c684(self);
            return;
        }
    }
    {
        unsigned char old = ((unsigned char *) self)[0xaf];
        void *p = func_ov002_02208008(self);
        if (func_ov002_022088ac(p) != 0) {
            if (((unsigned char *) self)[0xaf] != 0) {
                ((unsigned char *) self)[0xaf]--;
            }
        } else {
            if (func_ov002_0220889c(p) != 0) {
                if (((unsigned char *) self)[0xaf] < 1) {
                    ((unsigned char *) self)[0xaf]++;
                }
            }
        }
        {
            unsigned char cur = ((unsigned char *) self)[0xaf];
            if (old != cur) {
                if (cur != 0) {
                    int x = func_ov002_0220a768((char *) self + 0x1d4, 4);
                    int y = func_ov002_0220a72c((char *) self + 0x1d4, 4);
                    func_ov129_0229c368(self, x, y);
                } else {
                    int x = func_ov002_0220a768((char *) self + 0x1d4, 3);
                    int y = func_ov002_0220a72c((char *) self + 0x1d4, 3);
                    func_ov129_0229c368(self, x, y);
                }
            }
        }
    }
}
