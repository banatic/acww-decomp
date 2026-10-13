/* func_02036fec @ 0x02036fec, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02036fec {
    unsigned char pad_00[8];
    unsigned short h;
    unsigned char pad_0A;
    unsigned char b;
};

extern void *func_020984e8(void);
extern int func_020b22b8(void);
extern int func_020b22dc(void);
extern int func_02099020(void *p, int n);
extern void func_02099640(void *p);
extern int func_0209ac04(void);
extern void func_02035684(int a, int b, int c);
extern void func_02036fb4(struct UnkStruct_02036fec *p, int a, int b, int c);

void func_02036fec(struct UnkStruct_02036fec *self)
{
    self->b = 1;
    if (self->h == 0xffff) {
        void *r5 = func_020984e8();
        if (func_020b22b8() != 0) {
            func_02035684(3, 0, 5);
            func_02036fb4(self, 4, 0x45, 1);
            return;
        } else if (func_020b22dc() != 0) {
            func_02036fb4(self, 0xd, 0x4a, 0);
            return;
        } else {
            if (r5 != 0) {
                if (func_02099020(r5, 0x23) != 0) {
                    goto call_1c;
                }
                if (func_02099020(r5, 1) == 0) {
                    goto label_72;
                }
                func_02099640(r5);
                if (func_0209ac04() != 0) {
                    goto label_72;
                }
            call_1c:
                func_02036fb4(self, 0x1c, 0x46, 0);
                return;
            }
        label_72:
            if (r5 != 0) {
                if (func_02099020(r5, 1) == 0) {
                    return;
                }
                func_02036fb4(self, 0x1d, 0x48, 0);
            }
        }
    }
}
