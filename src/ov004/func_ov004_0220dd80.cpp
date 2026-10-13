/* func_ov004_0220dd80 @ 0x0220dd80, 0x260 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, z;
} Pair;
typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int tag;
    Pair a, b, n;
    int extra;
} Line;
extern "C" {
extern char *func_020961a8(int);
extern int func_ov004_0220cdd8(char *, int);
extern int func_020e8ed8(int, int);
extern void func_0202f8fc(Pair *, int, int);
extern int func_0202f59c(Line *, Pair *, Pair *, Pair *);
extern long long func_0202f838(Pair *, Pair *);
extern int FX_Sqrt(int);
extern int func_0202f464(Line *, Pair *);
extern void func_0203392c(Pair *, Line *);
extern int FX_MulFunc(int, int);
extern void func_0202f898(Pair *, Pair *, Pair *);
extern int func_0202f7f4(Pair *);
extern void func_ov004_0220dbac(char *, char *);
extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(void *, char *);
extern int func_ov004_0220fd8c(char *);
extern void func_ov004_0220fefc(char *, Vec *);
extern void *func_ov004_0223cd50(void);
extern char *func_ov004_0223cbe8(void *, Vec *, int);
extern int func_ov004_0220d4b4(void *);
extern int func_ov004_0220f240(int);
extern void *func_ov004_0223cb10(void);
extern int func_ov004_0223c758(void *, int, Vec *, Vec *, int, Vec *, Vec *, short, int);
}
#define OWNER (*(char **) (self + 0x9c))
extern "C" void func_ov004_0220dd80(char *self, Line *line, char *actor, int scale)
{
    int index, z, angle, opposite, length;
    int distance;
    u16 difference;
    short heading;
    int direction;
    char *peer;
    Pair a, b, intersection, midpoint, d1, d2;
    struct {
        Vec saved, center, destination, samples;
    } vectors;
    char *current = func_020961a8(4);
    if (!actor || actor != current) {
        return;
    }
    if (!OWNER) {
        return;
    }
    if (!func_ov004_0220cdd8(OWNER, 1)) {
        return;
    }
    angle = func_020e8ed8(line->n.x, line->n.z);
    opposite = angle + 0x8000;
    difference = (u16) (opposite - *(short *) (actor + 0x8e));
    {
        Vec *old = (Vec *) (actor + 0x68);
        vectors.saved.x = *(int *) (actor + 0x68);
        vectors.saved.y = old->y;
        vectors.saved.z = old->z;
    }
    func_0202f8fc(&a, vectors.saved.x, vectors.saved.z);
    func_0202f8fc(&b, vectors.saved.x + line->n.x, vectors.saved.z + line->n.z);
    func_0202f8fc(&intersection, 0, 0);
    if (!(difference < 0x1700 || difference > 0xe900)) {
        return;
    }
    if (!func_0202f59c(line, &intersection, &a, &b)) {
        return;
    }
    distance = FX_Sqrt(func_0202f838(&line->a, &intersection));
    length = FX_Sqrt(func_0202f838(&line->a, &line->b));
    if (distance < 0x666 || distance > length - 0x666) {
        return;
    }
    if (!func_0202f464(line, &intersection)) {
        return;
    }
    func_0203392c(&midpoint, line);
    z = midpoint.z + FX_MulFunc(line->n.z, scale);
    vectors.center.x = midpoint.x + FX_MulFunc(line->n.x, scale);
    vectors.center.y = 0;
    vectors.center.z = z;
    vectors.destination.x = vectors.center.x;
    vectors.destination.y = vectors.center.y;
    vectors.destination.z = vectors.center.z;
    if (length > 0x3000) {
        if (distance < 0x1000) {
            func_0202f898(&d1, &line->b, &line->a);
            func_0202f7f4(&d1);
            intersection.x = line->a.x + FX_MulFunc(d1.x, 0x1000);
            intersection.z = line->a.z + FX_MulFunc(d1.z, 0x1000);
        } else if (distance > 0x3000) {
            func_0202f898(&d2, &line->b, &line->a);
            func_0202f7f4(&d2);
            intersection.x = line->a.x + FX_MulFunc(d2.x, 0x3000);
            intersection.z = line->a.z + FX_MulFunc(d2.z, 0x3000);
        }
        z = intersection.z + FX_MulFunc(line->n.z, scale);
        vectors.destination.x = intersection.x + FX_MulFunc(line->n.x, scale);
        vectors.destination.y = 0;
        vectors.destination.z = z;
    }
    func_ov004_0220dbac(self, actor);
    index = func_ov004_0223cd78(func_ov004_0223ce84(), OWNER);
    heading = (short) (angle - *(short *) (OWNER + 0x8e));
    if (func_ov004_0220fd8c(OWNER) == 1) {
        func_ov004_0220fefc(OWNER, &vectors.samples);
        peer = func_ov004_0223cbe8(func_ov004_0223cd50(), &vectors.samples, 0);
        if (peer) {
            heading = (short) (angle - *(short *) (peer + 0x8e) - func_ov004_0220d4b4(OWNER + 0x17c));
        }
    }
    direction = func_ov004_0220f240(heading);
    func_ov004_0223c758(func_ov004_0223cb10(), index, (Vec *) (actor + 0x68), (Vec *) (actor + 0x5c), scale, &vectors.center,
                        &vectors.destination, (short) opposite, direction);
}
