/* func_ov003_022286f4 @ 0x022286f4, 0x90 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern char data_ov003_0225f220[];
extern void func_ov003_022286ac(void *a0, Vec3 *p, char *q, int ang);
extern void func_02055124(void *p);
extern void func_02056ffc(void *p);

void func_ov003_022286f4(void *a0, char *src)
{
    char (*gp)[] = &data_ov003_0225f220;
    char *g = (char *) (*gp);
    Vec3 *p = (Vec3 *) (src + 0x120);
    char *q;
    char *r;
    int ang;
    *(int *) (g + 0x48) = p->x;
    *(int *) (g + 0x4c) = p->y;
    *(int *) (g + 0x50) = p->z;
    ang = *(short *) (src + 0x138);
    *(short *) (g + 0x54) = ang;
    q = g + 0x58;
    *(int *) (q + 0xac) = *(int *) (src + 0x1f0);
    *(unsigned int *) (q + 0xa4) = (((((unsigned int) *(int *) (src + 0x1e8) << 4) >> 16) + 1) << 16) >> 4;
    func_ov003_022286ac(a0, p, q, ang);
    func_02055124(src + 0x144);
    func_02055124(q);
    r = g + 0x11c;
    func_02056ffc(r);
    **(int **) (r + 0x18) = *(int *) (r + 8);
}
