/* func_02015b9c @ 0x02015b9c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02015da0(void *self, int param);
extern void func_02015c3c(void *self, void *a);
extern void func_0201ad18(void *p, int a, int b, void *c, int d, int e, int f, int g);

extern unsigned char data_021fbee8[];

void func_02015b9c(void *self)
{
    void *a;
    void *b;
    unsigned char state;

    a = func_02015da0(self, 0);
    if (a == 0) {
        return;
    }

    state = ((unsigned char *) self)[0x54];
    switch (state) {
        case 1:
            b = func_02015da0(self, state);
            if (b != 0) {
                func_0201ad18((char *) b + 0x3b0, 2, 0, a, (unsigned int) data_021fbee8, 4, 0, 0);
            }
            break;
        case 2:
            func_02015c3c(self, a);
            break;
    }
}
