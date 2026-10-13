/* func_ov003_02228400 @ 0x02228400, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern char data_ov003_0225f76c[];
extern int func_020ea990(Vec3 *v, void *a);
extern int func_ov003_022282b8(void *e, void *a);

int func_ov003_02228400(void *a, int lim)
{

    int i;
    char *e;
    int found;
    Vec3 v;
    Vec3 *p;

    found = 0;
    e = data_ov003_0225f76c;
    for (i = 0; i < 6; i++) {
        p = (Vec3 *) (e + 0x120);
        v.x = p->x;
        v.y = p->y;
        v.z = p->z;
        if (func_020ea990(&v, a) <= lim) {
            if (func_ov003_022282b8(e, a)) {
                found = 1;
            }
        }
        e += 0x24c;
    }
    return found;
}
