/* func_ov046_022608a4 @ 0x022608a4, 0x3e bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022608a4 {
    char pad_00[0xc0];
    int c0;
    char c4;
    char c5;
    char pad_C6[0x16];
    int dc;
};

extern int func_020b14c0(int);
extern int func_020b1558(int);

void func_ov046_022608a4(struct UnkStruct_022608a4 *self, int flag)
{
    int x;

    if (flag == 0) {
        x = self->c0;
        if (x < 0) {
        } else {
            x = func_020b14c0(x);
        }
        self->c5 = (char) (16 - func_020b1558(x));
        self->c4 = 0;
        self->dc = 0x21;
    } else {
        self->dc = 9;
    }
}
