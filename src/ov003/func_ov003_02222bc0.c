/* func_ov003_02222bc0 @ 0x02222bc0, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov003_02222b68(void *, int, int);
extern void *func_02064b2c(void *, void *, int, void *);
extern void *NNS_G3dGetJntAnmSet(void *);
extern void *func_02107b44(void *, void *);
extern void *data_ov003_0223cf78;

void func_ov003_02222bc0(void *self)
{
    int i = 0;
    int j = 0;
    void *z1 = 0;
    void *z2 = 0;
    void *z3 = 0;
    void **q;
    void **slot;
    void *res;
    char *row;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            row = (char *) self + i * 0x10;
            res = func_ov003_02222b68(self, i, j);
            if (res != 0) {
                q = (void **) (row + j * 4);
                *(void **) (row + j * 4) = func_02064b2c(res, data_ov003_0223cf78, 4, z1);
                q += 0x20;
                *q = func_02107b44(NNS_G3dGetJntAnmSet(*(void **) (row + j * 4)), z2);
            } else {
                slot = (void **) (row + j * 4);
                *(void **) (row + j * 4) = z3;
                *(void **) ((char *) slot + 0x80) = z3;
            }
        }
    }
}
