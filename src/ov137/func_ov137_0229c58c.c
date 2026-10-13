/* func_ov137_0229c58c @ 0x0229c58c, 0x9c bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov137_0229d35c[];
extern unsigned char data_ov137_0229d358[];
extern unsigned char data_ov137_0229d364[];
extern unsigned char data_ov137_0229d360[];
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);

struct func_ov137_0229c58c_s {
    unsigned char pad_00[0x2b77];
    unsigned char byte;
};

int func_ov137_0229c58c(struct func_ov137_0229c58c_s *self, int param)
{
    unsigned char old;

    old = self->byte;
    if (func_ov002_022088ac(param)) {
        self->byte = data_ov137_0229d35c[self->byte];
    } else if (func_ov002_0220889c(param)) {
        self->byte = data_ov137_0229d358[self->byte];
    }
    if (old != self->byte) {
        return 1;
    }
    if (func_ov002_022088cc(param)) {
        self->byte = data_ov137_0229d364[self->byte];
    } else if (func_ov002_022088bc(param)) {
        self->byte = data_ov137_0229d360[self->byte];
    }
    if (old != self->byte) {
        return 1;
    }
    return 0;
}
