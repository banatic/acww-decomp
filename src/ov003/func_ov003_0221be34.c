/* func_ov003_0221be34 @ 0x0221be34, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct SelfType {
    char pad_00[0x136];
    unsigned short unk_136;
    char pad_138[0x236 - 0x136 - 2];
    unsigned char unk_236;
} SelfType;

extern int func_020b2470(int);
extern void func_ov003_0221bfa8(void *self, int n);

void func_ov003_0221be34(SelfType *self)
{
    int state = func_020b2470(self->unk_136);
    if (state != 0) {
        int flag;
        unsigned int v;
        if (state == 2) {
            flag = 1;
        } else {
            flag = 0;
        }
        v = self->unk_236;
        v &= ~2;
        v |= (flag & 1) << 1;
        self->unk_236 = (unsigned char) v;
        func_ov003_0221bfa8(self, 2);
    }
}
