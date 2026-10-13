/* func_020b75b8 @ 0x020b75b8, 0x73c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" {
#pragma opt_loop_invariants off
#pragma opt_propagation off

typedef struct {
    int x, y, z;
} Vec3;

#define W(p, o) (*(int *) ((u8 *) (p) + (o)))
#define B(p, o) (*(u8 *) ((u8 *) (p) + (o)))
#define P(p, o) (*(void **) ((u8 *) (p) + (o)))

extern int data_021c8c9c;
extern u8 *data_021f6948;
extern u32 data_021f6ad0;
extern int data_021f6ad4;
extern u32 data_021f6ac8;
extern int data_021f6ad8;
extern int data_020ca0ec;
extern int data_020ca0e8;
extern int data_020c904c;
extern void *data_021c67a4;
extern Vec3 data_021c67d0;
extern void *data_021d3120;
extern u8 data_020e54a8;

extern void func_020b7e9c(void *p, int param);
extern void func_020b8314(void *out, int px, int pz);
extern int func_020b8550(Vec3 *out, Vec3 *from, Vec3 *to, int a4, int a5);
extern int func_0203f7d0(Vec3 *out, const Vec3 *in);
extern int func_02034270(void *obj, Vec3 *v, int a, int b);
extern void func_0203423c(void *obj);
extern int func_020b758c(void *src, void *dst);
extern int func_0203f758(void);
extern void func_020eabc8(Vec3 *v, int scale);
extern void func_01ffd070(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern short func_0203c590(void *p);
extern void func_020e9684(void *mtx, int angle);
extern void func_020e9868(void *mtx, int x, int y, int z);
extern void func_020e9774(void *mtx, int angle);
extern void MTX_MultVec43(const Vec3 *v, const void *m, Vec3 *dst);
extern void func_0202fc5c(Vec3 *nrm, Vec3 *a, Vec3 *b, Vec3 *c);
extern void *func_0202feb4(void *obj, Vec3 *a, Vec3 *b, Vec3 *c, Vec3 *nrm);
extern int func_0202fb28(void *tri, const Vec3 *p);
extern int func_0202f9d0(void *tri, Vec3 *out, Vec3 *a, Vec3 *b);
extern void func_0202fee0(void *obj);
extern int func_02034240(void *obj, int gx, int gz, int a3, int a4);
extern int func_020341c8(void *obj, int flag);
extern void func_0202feec(void *obj);
extern int func_0202fc18(void *obj, Vec3 *a, Vec3 *b, Vec3 *c, Vec3 *nrm);
extern void func_020eaca0(Vec3 *dst, const Vec3 *a, const Vec3 *b);
extern int FX_Div(int numer, int denom);
extern int FX_MulFunc(int a, int b);
extern int func_020b83ec(Vec3 *self, Vec3 *from, void *p2, int p3, int p4);
extern u8 func_020b8538(int kind);
extern int func_02031078(int gx, int gz, int *o1, int *o2, int *o3);
extern void func_0204f818(int *o0, int *o1, const int *in);
extern int func_0202f1cc(void *node, Vec3 *out, void *seg);
extern int func_0203005c(void *seg, const Vec3 *a, const Vec3 *b);
extern void func_02030058(void *seg);
extern void *func_ov003_022201fc(unsigned int a, unsigned int b);
extern int func_ov003_02220150(int x);

class Actor {
  public:
    virtual Vec3 *position();
};
static inline Vec3 *actor_pos(void *self)
{
    return ((Actor *) self)->position();
}
void func_020b75b8(int a, unsigned char b, unsigned char c, int flag)
{
    void *self = (void *) a;

    struct {
        Vec3 origin, far_, dir;
    } ray;

    Vec3 from;
    Vec3 to;
    Vec3 hit;
    Vec3 tmp;
    unsigned char probe[0x40];
    int i, j;
    int cleared;
    Vec3 *farPtr;

    func_020b7e9c(self, flag);

    if (flag == 0 || data_021c8c9c == 1) {
        P(self, 0x20) = 0;
        P(self, 0x24) = 0;
        P(self, 0x1c) = 0;
        return;
    }

    func_020b8314(&ray, (int) b, (int) c);
    from.x = ray.origin.x;
    from.y = ray.origin.y;
    from.z = ray.origin.z;
    farPtr = &ray.far_;
    to.x = farPtr->x;
    to.y = farPtr->y;
    to.z = farPtr->z;

    // The outer-world band extends the ray before testing its two faces.
    if (data_021f6948[4] == 1) {

        int span, groundy;

        if ((data_021f6ad0 & 1) == 0) {
            data_021f6ad4 = 6 * data_020ca0ec;
            data_021f6ad0 |= 1;
        }
        if ((data_021f6ac8 & 1) == 0) {
            data_021f6ad8 = data_020c904c + func_0203f758();
            data_021f6ac8 |= 1;
        }
        span = data_021f6ad4;

        if (func_020b8550(&hit, &from, &to, data_021f6ad8, span)) {
            func_0203f7d0(&tmp, &hit);
            func_02034270(probe, &tmp, 0, 0);
            if (W(probe, 0x30) != 0) {
                to.x = hit.x;
                to.y = hit.y;
                to.z = hit.z;
                tmp.y = data_020c904c;
                W(self, 0x00) = tmp.x;
                W(self, 0x04) = tmp.y;
                W(self, 0x08) = tmp.z;
            }
            func_0203423c(probe);
        }

        if (!func_020b758c(self, 0)) {
            Vec3 tmp2;
            if (func_020b8550(&hit, &from, &to, func_0203f758(), span)) {
                to.x = hit.x;
                to.y = hit.y;
                to.z = hit.z;
                func_0203f7d0(&tmp2, &hit);
                tmp2.y = 0;
                W(self, 0x00) = tmp2.x;
                W(self, 0x04) = tmp2.y;
                W(self, 0x08) = tmp2.z;
            }
        }

        if (!func_020b758c(self, 0)) {
            void *world = data_021c67a4;
            if (world != 0) {
                struct {
                    Vec3 extent, dir;
                } extentDir;
                Vec3 tip;
                Vec3 corner[4];
                unsigned char mtx[0x30];
                Vec3 q[4];
                Vec3 nrm;
                Vec3 out;
                Vec3 tmp3;
                unsigned char quad[2][0x38];
                int reach, half, lo, hi, edge;
                Vec3 *direction;
                unsigned char *walk;
                unsigned qi;

                extentDir.extent.x = data_021c67d0.x;
                extentDir.extent.y = data_021c67d0.y;
                extentDir.extent.z = data_021c67d0.z;
                direction = &ray.dir;
                extentDir.dir.x = direction->x;
                extentDir.dir.y = direction->y;
                extentDir.dir.z = direction->z;
                reach = data_020ca0e8;
                func_020eabc8(&extentDir.dir, reach << 2);
                func_01ffd070(&tip, &from, &extentDir.dir);

                half = data_020ca0ec;
                lo = extentDir.extent.x - half;

                corner[0].x = lo;
                corner[0].y = reach;
                corner[0].z = 0;
                corner[1].x = lo;
                edge = (int) 0xffffe000;
                corner[1].y = edge;
                corner[1].z = 0;
                hi = extentDir.extent.x + half;
                corner[2].x = hi;
                corner[2].y = edge;
                corner[2].z = 0;
                corner[3].x = hi;
                corner[3].y = reach;
                corner[3].z = 0;

                func_020e9684(mtx, func_0203c590(world));
                func_020e9868(mtx, 0, func_0203f758(), 0);
                func_020e9774(mtx, (int) 0xfffff000);
                func_020e9774(mtx, 0);

                MTX_MultVec43(&corner[0], mtx, &q[0]);
                MTX_MultVec43(&corner[1], mtx, &q[1]);
                MTX_MultVec43(&corner[2], mtx, &q[2]);
                MTX_MultVec43(&corner[3], mtx, &q[3]);

                func_0202fc5c(&nrm, &q[0], &q[1], &q[2]);
                func_0202feb4(quad[0], &q[0], &q[1], &q[2], &nrm);
                func_0202feb4(quad[1], &q[0], &q[2], &q[3], &nrm);

                walk = (unsigned char *) quad;
                qi = 0;
                do {

                    if (func_0202fb28(walk, &from) >= 0 && ((func_0202fb28(walk, &tip) >= 0) ? 1 : 0) == 0) {
                        if (func_0202f9d0(walk, &out, &from, &tip)) {
                            to.x = out.x;
                            to.y = out.y;
                            to.z = out.z;
                            func_0203f7d0(&tmp3, &out);
                            W(self, 0x00) = tmp3.x;
                            W(self, 0x04) = tmp3.y;
                            W(self, 0x08) = tmp3.z;
                            W(self, 0x04) = 0;
                        }
                    }
                    walk += 0x38;
                    ++qi;
                } while (qi < 2);
                func_0202fee0(quad[1]);
                func_0202fee0(quad[0]);
            }
        }
    } else {

        // Inclusive cell bounds; each cell owns two temporary wall faces.
        int ax = from.x >> 13, az = from.z >> 13;
        int bx = to.x >> 13, bz = to.z >> 13;
        int xlo, zlo, xhi, zhi;
        int found;

        if (ax <= bx) {
            xlo = ax;
            xhi = bx;
        } else {
            xlo = bx;
            xhi = ax;
        }
        if (az <= bz) {
            zlo = az;
            zhi = bz;
        } else {
            zlo = bz;
            zhi = az;
        }

        found = 0;

        for (i = xlo; i <= xhi; i++) {
            int cx;
            j = zlo;
            cx = (i << 13) + 0x1000;
            for (; j <= zhi; j++) {
                unsigned char cell[0x40];
                unsigned char wall[2][0x38];
                struct {
                    Vec3 dead, corner[4];
                } corners;
                Vec3 up;
                Vec3 out;
                int cz, h;
                unsigned char *walk;
                unsigned k;

                func_02034240(cell, i, j, 0, 0);
                h = func_020341c8(cell, 0);
                if (h >= 0x4000 || h == 0) {
                    goto cell_done;
                }

                // z is initialized where it is stored.
                corners.dead.x = cx;
                corners.dead.y = 0;
                cz = (j << 13) + 0x1000;
                corners.dead.z = cz;
                corners.corner[0].x = cx;
                corners.corner[0].y = 0;
                corners.corner[0].z = cz;
                corners.corner[1].x = cx;
                corners.corner[1].y = 0;
                corners.corner[1].z = cz;
                corners.corner[2].x = cx;
                corners.corner[2].y = 0;
                corners.corner[2].z = cz;
                corners.corner[3].x = cx;
                corners.corner[3].y = 0;
                corners.corner[3].z = cz;

                corners.corner[0].x = cx - 0x1000;
                corners.corner[0].y = h;
                corners.corner[0].z = cz - 0x1000;
                corners.corner[1].x = cx - 0x1000;
                corners.corner[1].y = h;
                corners.corner[1].z = cz + 0x1000;
                corners.corner[2].x = cx + 0x1000;
                corners.corner[2].y = h;
                corners.corner[2].z = cz + 0x1000;
                corners.corner[3].x = cx + 0x1000;
                corners.corner[3].y = h;
                corners.corner[3].z = cz - 0x1000;
                up.x = 0;
                up.y = 0x1000;
                up.z = 0;

                func_0202feec(wall[0]);
                func_0202feec(wall[1]);
                func_0202fc18(wall[0], &corners.corner[0], &corners.corner[1], &corners.corner[3], &up);
                func_0202fc18(wall[1], &corners.corner[1], &corners.corner[2], &corners.corner[3], &up);

                walk = (unsigned char *) wall;
                k = 0;
                do {
                    if (func_0202fb28(walk, &from) >= 0 && ((func_0202fb28(walk, &to) >= 0) ? 1 : 0) == 0) {
                        if (func_0202f9d0(walk, &out, &from, &to)) {
                            to.x = out.x;
                            to.y = out.y;
                            to.z = out.z;
                            W(self, 0x00) = to.x;
                            W(self, 0x04) = to.y;
                            W(self, 0x08) = to.z;
                            found = 1;
                        }
                    }
                    walk += 0x38;
                    ++k;
                } while (k < 2);
                func_0202fee0(wall[1]);
                func_0202fee0(wall[0]);
            cell_done:
                func_0203423c(cell);
            }
        }

        if (!found && from.y > 0 && to.y <= 0) {
            struct {
                Vec3 d, unused;
            } plane;
            unsigned char probe2[0x40];
            int num, den, t;

            func_020eaca0(&plane.d, &to, &from);
            num = (from.y < 0) ? -from.y : from.y;
            den = from.y - to.y;
            if (den < 0) {
                den = -den;
            }
            t = FX_Div(num, den);

            hit.x = from.x + FX_MulFunc(plane.d.x, t);
            hit.y = from.y + FX_MulFunc(plane.d.y, t);
            hit.z = from.z + FX_MulFunc(plane.d.z, t);
            to.x = hit.x;
            to.y = hit.y;
            to.z = hit.z;

            func_02034270(probe2, &hit, 0, 0);
            W(self, 0x00) = hit.x;
            W(self, 0x04) = hit.y;
            W(self, 0x08) = hit.z;
            func_0203423c(probe2);
        }
    }

    {
        void *n = P(self, 0x24);
        while (n != 0) {
            if (func_020b83ec(&to, &from, n, W(n, 0x0c), W(n, 0x10))) {
                W(self, 0x0c) = W(n, 0x00);
                W(self, 0x10) = W(n, 0x04);
                W(self, 0x14) = W(n, 0x08);
                B(self, 0x18) = (u8) W(n, 0x14);
                B(self, 0x19) = B(n, 0x18);
            }
            n = P(n, 0x1c);
        }
    }

    {
        void *n = data_021d3120;
        while (n != 0) {
            if (func_020b8538((int) B(n, 0x0c))) {
                Vec3 *pos = actor_pos(n);
                if (func_020b83ec(&to, &from, pos, W(n, 0x04), W(n, 0x08))) {
                    Vec3 *p2 = actor_pos(n);
                    W(self, 0x0c) = p2->x;
                    W(self, 0x10) = p2->y;
                    W(self, 0x14) = p2->z;
                    B(self, 0x18) = B(n, 0x0c);
                    B(self, 0x19) = B(n, 0x0d);
                }
            }
            n = P(n, 0x38);
        }
    }

    {
        // Acre queries run in descending order after world-to-map conversion.
        struct {
            Vec3 pa, pb, lo, hi;
        } bounds;
        int x0, x1, z0, z1;

        func_0203f7d0(&bounds.pa, &from);
        func_0203f7d0(&bounds.pb, &to);

        if (bounds.pa.x < bounds.pb.x) {
            bounds.lo.x = bounds.pa.x;
            bounds.hi.x = bounds.pb.x;
        } else {
            bounds.lo.x = bounds.pb.x;
            bounds.hi.x = bounds.pa.x;
        }
        bounds.pb.y = 0;
        bounds.pa.y = 0;
        if (bounds.pa.z < bounds.pb.z) {
            bounds.lo.z = bounds.pa.z;
            bounds.hi.z = bounds.pb.z;
        } else {
            bounds.lo.z = bounds.pb.z;
            bounds.hi.z = bounds.pa.z;
        }

        x0 = bounds.lo.x >> 13;
        z0 = bounds.lo.z >> 13;
        x1 = bounds.hi.x >> 13;
        z1 = bounds.hi.z >> 13;

        for (j = z1; j >= z0; j--) {
            int cz;
            i = x1;
            cz = (j << 13) + 0x1000;
            for (; i >= x0; i--) {
                int o1, o2, o3;
                Vec3 cell;

                o3 = 0;
                if (!func_02031078(i, j, &o1, &o2, &o3)) {
                    continue;
                }
                if (o3 == 0) {
                    continue;
                }

                cell.x = (i << 13) + 0x1000;
                cell.y = 0;
                cell.z = cz;

                if (func_020b83ec(&to, &from, &cell, o1, o2)) {
                    W(self, 0x0c) = cell.x;
                    W(self, 0x10) = cell.y;
                    W(self, 0x14) = cell.z;
                    cleared = 0;
                    B(self, 0x19) = cleared;
                    if (((data_020e54a8 == 0) ? 1 : cleared) != 0) {
                        if (o3 == 10) {

                            int hx, hz;
                            B(self, 0x18) = 6;
                            func_0204f818(&hx, &hz, (const int *) ((u8 *) self + 0x0c));
                            B(self, 0x19) =
                                (u8) func_ov003_02220150((int) func_ov003_022201fc((unsigned int) hx, (unsigned int) hz));
                        } else {
                            B(self, 0x18) = 5;
                        }
                    } else {
                        B(self, 0x18) = 5;
                    }
                }
            }
        }
    }

    {
        void *n = P(self, 0x1c);
        Vec3 out;
        Vec3 t;
        while (n != 0) {
            // Reject a back-facing origin before testing the endpoint.
            if (func_0202fb28(n, &from) >= 0 && ((func_0202fb28(n, &to) >= 0) ? 1 : 0) == 0) {
                if (func_0202f9d0(n, &out, &from, &to)) {
                    to.x = out.x;
                    to.y = out.y;
                    to.z = out.z;
                    func_0203f7d0(&t, &to);
                    W(self, 0x0c) = t.x;
                    W(self, 0x10) = t.y;
                    W(self, 0x14) = t.z;
                    B(self, 0x18) = (u8) W(n, 0x3c);
                    B(self, 0x19) = B(n, 0x40);
                }
            }
            n = P(n, 0x38);
        }
        {
            void *n = P(self, 0x20);
            unsigned char seg[0x24];
            Vec3 t;
            while (n != 0) {
                func_0203005c(seg, &from, &to);
                if (func_0202f1cc(n, &out, seg)) {
                    func_0203f7d0(&t, (const Vec3 *) n);
                    W(self, 0x0c) = t.x;
                    W(self, 0x10) = t.y;
                    W(self, 0x14) = t.z;
                    B(self, 0x18) = (u8) W(n, 0x14);
                    B(self, 0x19) = B(n, 0x10);
                }
                n = P(n, 0x18);
                func_02030058(seg);
            }
        }
    }
    P(self, 0x20) = 0;
    P(self, 0x24) = 0;
    P(self, 0x1c) = 0;
}
}
