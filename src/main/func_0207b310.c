/* func_0207b310 @ 0x0207b310, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0207b310 {
    char pad_00[0x4076];
    signed char unk_4076;
} UnkStruct_0207b310;

extern unsigned short data_020cd4c4[];

extern void func_0209e474(void *p);
extern int func_0208150c(char *p);
extern int func_02003704(int x);
extern int func_0207f150(char *p);
extern int func_0207dca8(char *p);
extern int func_02080998(char *p, int n, void *buf);
extern int func_0207cc54(int a, int b, int c);
extern void *func_0207cec0(UnkStruct_0207b310 *self, int i);
extern unsigned char *func_02080890(void *e);
extern int func_020644cc(int x);

int func_0207b310(UnkStruct_0207b310 *self, unsigned int k)
{
    // DECLS
    int cnt;
    int z;
    int buf[2];
    unsigned char mask;
    char *p;
    int i;
    int sel;
    void *e;
    unsigned char *q;
    // ENDDECLS

    if (k >= 0xc) {
        return -1;
    }
    mask = 0;
    buf[0] = 0;
    buf[1] = 0;
    p = (char *) self;
    cnt = 0;
    func_0209e474(buf);
    for (i = 0; i < 8; i++) {
        z = 0;
        if (i != self->unk_4076) {
            if (func_02003704(func_0208150c(p))) {
                if (func_0207f150(p) == 3) {
                    if (func_0207dca8(p) != 0) {
                        if (func_02080998(p, 0xf, buf) == ~z) {
                            mask |= 1 << i;
                            cnt++;
                        }
                    }
                }
            }
        }
        p += 0x7ec;
    }
    sel = func_0207cc54(mask, cnt, 8);
    e = func_0207cec0(self, sel);
    if (e != 0) {
        q = func_02080890(e);
        if (func_020644cc(data_020cd4c4[k]) < q[3] + 0x80) {
            return sel;
        }
    }
    return -1;
}
