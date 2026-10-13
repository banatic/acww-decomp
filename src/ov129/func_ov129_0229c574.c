/* func_ov129_0229c574 @ 0x0229c574, 0x9c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);

extern unsigned char data_ov129_0229dae4[];
extern unsigned char data_ov129_0229daf4[];
extern unsigned char data_ov129_0229dafc[];
extern unsigned char data_ov129_0229daec[];

typedef struct {
    unsigned char pad_00[0xae];
    unsigned char key;
} func_ov129_0229c574_self;

int func_ov129_0229c574(func_ov129_0229c574_self *self, void *arg)
{
    unsigned char old;
    unsigned char idx;

    old = self->key;

    if (func_ov002_022088ac(arg)) {
        idx = self->key;
        self->key = data_ov129_0229dae4[idx];
    } else if (func_ov002_0220889c(arg)) {
        idx = self->key;
        self->key = data_ov129_0229daf4[idx];
    } else if (func_ov002_022088cc(arg)) {
        idx = self->key;
        self->key = data_ov129_0229dafc[idx];
    } else if (func_ov002_022088bc(arg)) {
        idx = self->key;
        self->key = data_ov129_0229daec[idx];
    }

    return old != self->key;
}
