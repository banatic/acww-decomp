/* func_ov003_0221d2b0 @ 0x0221d2b0, 0xf4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_02264c40(void *self);
extern void *func_0207cec0(void *tbl, int id);
extern int func_0207f1d4(void *handle);
extern int func_0207f1d8(void *p);
extern int func_02073dd4(void *g, unsigned int i);
extern void func_020a6e4c(unsigned int i, unsigned char *a, unsigned char *b, unsigned char *c);
extern int func_020b66c4(unsigned char v);

extern int data_021e5a2c;
extern void *data_020ccf94;

typedef struct {
    char pad_00[0x136];
    unsigned short unk_136;
} UnkStruct_0221d2b0;

int func_ov003_0221d2b0(UnkStruct_0221d2b0 *self)
{
    unsigned char b[3];
    unsigned int ok;
    unsigned short v;
    int id;
    void *p;
    void *g;
    unsigned int i;

    ok = 0;
    v = self->unk_136;
    if (v >= 0x5001 && v <= 0x5008) {
        ok = 1;
    }
    if (ok > 0) {
        id = v - 0x5001;
    } else {
        id = -1;
    }
    if (func_ov009_02264c40(self) != 0) {
        p = func_0207cec0(&data_021e5a2c, id);
        if (p != 0) {
            if (func_0207f1d4(p) == 0) {
                return 0;
            }
            if (func_0207f1d8(p) == 0 || func_0207f1d8(p) == 3 || func_0207f1d8(p) == 4 || func_0207f1d8(p) == 5 ||
                func_0207f1d8(p) == 6 || func_0207f1d8(p) == 7) {
                return 0;
            }
            if (func_0207f1d8(p) == 2) {
                i = 0;
                g = data_020ccf94;
                for (; i < 4; i++) {
                    if (func_02073dd4(g, i) != 0) {
                        func_020a6e4c(i, &b[0], &b[1], &b[2]);
                        if (id == func_020b66c4(b[0])) {
                            return 1;
                        }
                    }
                }
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
