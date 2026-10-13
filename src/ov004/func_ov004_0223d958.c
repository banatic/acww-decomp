/* func_ov004_0223d958 @ 0x0223d958, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020961a8(int);
extern void *data_ov004_02259a14;
struct UnkStruct_0223d958 {
    int x;
    int y;
    int z;
};

void *func_ov004_0223d958(char *self)
{
    // DECLS
    int dz;
    char *g;
    int ex;
    int dx;
    void *n;
    int ez;
    struct UnkStruct_0223d958 *pn;
    struct UnkStruct_0223d958 *pg;
    struct UnkStruct_0223d958 *ps;
    // ENDDECLS
    n = func_020961a8(4);
    g = (char *) data_ov004_02259a14;
    if (g == 0) {
        return n;
    }
    if (n != 0) {
        ps = (struct UnkStruct_0223d958 *) (self + 0x5c);
        pn = (struct UnkStruct_0223d958 *) ((char *) n + 0x5c);
        pg = (struct UnkStruct_0223d958 *) (g + 0x5c);
        dx = ps->x - pn->x;
        if (dx < 0) {
            dx = -dx;
        }
        dz = ps->z - pn->z;
        if (dz < 0) {
            dz = -dz;
        }
        ex = ps->x - pg->x;
        if (ex < 0) {
            ex = -ex;
        }
        ez = ps->z - pg->z;
        if (ez < 0) {
            ez = -ez;
        }
        if (dx + dz <= ex + ez) {
            return n;
        }
    }
    return g;
}
