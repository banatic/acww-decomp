/* func_020797bc @ 0x020797bc, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#define G ((void *) 0x021e5a2c)

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} Box;

typedef struct {
    char pad_00[0x168];
    int unk_168;
} Res;

extern void func_0209e474(void *p);
extern void *func_0207cec0(void *g, int i);
extern int func_0208150c(void *e);
extern int func_02003704(int x);
extern int func_0207f1c8(void *e);
extern int func_0209b5ec(int x);
extern int func_0209c1c0(int x, void *buf);
extern int func_020798a0(unsigned short *h, int x0, int x1, int x2, int x3);
extern void func_0207dac8(void *e, int a, int mode);
extern Res *func_02079350(void);

void func_020797bc(int a, Box *b)
{
    void *e;
    int x3;
    int x0;
    unsigned short h;
    int i;
    int x1;
    int x2;
    int buf[2];
    int mode;

    if (G != 0) {
        x0 = 0;
        buf[0] = 0;
        buf[1] = 0;
        x1 = 0;
        x2 = 0;
        x3 = 0;
        h = 0xfff1;
        if (b != 0) {
            x0 = b->unk_00 - 0x10000;
            x1 = b->unk_00 + 0x10000;
            x2 = b->unk_08 - 0x1a000;
            x3 = b->unk_08 + 0xa000;
        }
        func_0209e474(buf);
        for (i = 0; i < 8; i++) {
            mode = 1;
            e = func_0207cec0(G, i);
            if (e != 0) {
                if (func_02003704(func_0208150c(e))) {
                    if (func_0209c1c0(func_0209b5ec(func_0207f1c8(e)), buf)) {
                        if (b != 0) {
                            h = (unsigned short) ((i & 0xfff) | 0xe000);
                            if (func_020798a0(&h, x0, x1, x2, x3)) {
                                mode = 2;
                            }
                        }
                        func_0207dac8(e, a, mode);
                    }
                }
            }
        }
        func_02079350()->unk_168 = 0;
    }
}
