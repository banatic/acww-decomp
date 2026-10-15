/* func_ov077_022790c4 @ 0x022790c4, 0x170 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022790c4 {
    int x, y;
    UnkStruct_022790c4(int a, int b) : x(a), y(b) {}
};

extern "C" void *func_02096190(int k);
extern "C" void func_020ee470(void *self);
extern "C" void func_0204f818(int *px, int *pz, void *p);
extern "C" short func_0201c314(void *self, void *o);
extern "C" void func_0204f794(void *p, int x, int z);
extern "C" int func_0203e070(void *self, int k);

extern "C" int func_ov077_022790c4(char *self)
{
    int dx, dz;
    int bx1, by1;
    int bx0, by0;
    int px, pz;
    int pos[3];
    char *o;
    int *p;
    int i;
    int ax, ay;
    UnkStruct_022790c4 *e;
    short r;

    o = (char *) func_02096190(4);
    if (o == 0) {
        func_020ee470(self);
        return 1;
    }
    *(int *) (self + 0x198) = 0;
    *(int *) (self + 0x190) = 0;
    p = (int *) (o + 0x5c);
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];
    px = 0;
    pz = 0;
    func_0204f818(&px, &pz, pos);
    dx = px - *(int *) (self + 0x71c);
    dz = pz - *(int *) (self + 0x720);
    r = func_0201c314(self, o);
    *(short *) (self + 0x8e) = r;
    *(short *) (self + 0x94) = r;
    static UnkStruct_022790c4 tbl[5] = {UnkStruct_022790c4(0, 3), UnkStruct_022790c4(-1, 3), UnkStruct_022790c4(-1, 2),
                                        UnkStruct_022790c4(1, 3), UnkStruct_022790c4(1, 2)};
    static UnkStruct_022790c4 tbl2[2] = {UnkStruct_022790c4(-2, 2), UnkStruct_022790c4(2, 2)};
    i = 0;
    bx1 = tbl2[1].x;
    by1 = tbl2[1].y;
    bx0 = tbl2[0].x;
    by0 = tbl2[0].y;
    for (; i < 5; i++) {
        unsigned int ok = 0;
        e = &tbl[i];
        if (e->x == dx && e->y == dz) {
            ok = 1;
        }
        if (ok != 0) {
            if (i <= 2) {
                ax = bx1 + *(int *) (self + 0x71c);
                ay = by1 + *(int *) (self + 0x720);
            } else {
                ax = bx0 + *(int *) (self + 0x71c);
                ay = by0 + *(int *) (self + 0x720);
            }
            func_0204f794(self + 0x5c, ax, ay);
            func_0203e070(self, 0);
        }
    }
    return 1;
}
