/* func_ov004_0223f41c @ 0x0223f41c, 0x280 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int v[12];
} Mat;
#define B(p, o) (*(u8 *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define W(p, o) (*(int *) ((p) + (o)))
extern void func_ov004_0223f69c(void *, char *, Vec *);
extern int func_02089cc0(void *, int);
extern int func_ov004_0223f398(void *, int, u8);
extern int func_02055d0c(void *, Mat *, int);
extern int func_0203f7d0(Vec *, Vec *);
extern void func_02031288(void *, Vec *, Vec *, int, int, int, int);
extern void func_02089bec(void *, Vec *, int, int, int, int, int, u8, int);
extern void func_02089fc8(void *);
extern void func_02055124(void *);
extern void func_02056ffc(void *);
extern int func_ov004_02244ae4(signed char, int);
extern void func_020042c0(void *, Vec *);
extern int func_0203f8d0(Vec *, Vec *);
extern void func_020e96c8(Mat *, int, int, int);
extern void func_020e9774(Mat *, int);
extern void func_020e9744(Mat *, int);
extern void func_020e9714(Mat *, int);
extern short data_ov004_0225630a[];
extern u8 data_ov004_02256308[];
extern Mat data_021fbe48;
static inline void copy(Vec *d, const Vec *s)
{
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}
void func_ov004_0223f41c(void *manager, char *obj)
{
    int scale;
    char *effect;
    Vec *position;
    int kind, flags, heading;
    Vec previous, origin;
    Mat matrix;
    Vec emitPosition, translated, temp;
    if (*(void (**)(char *))(obj + 0x2d4) == 0) {
        return;
    }
    effect = obj + 0x19c;
    position = (Vec *) (obj + 0x2c8);
    kind = B(obj, 0x196);
    copy(&previous, position);
    if (B(effect, 0x3c)) {
        position->x += W(effect, 0x10);
        position->z += W(effect, 0x18);
        func_ov004_0223f69c(manager, obj, &previous);
        if (func_02089cc0(effect, 0x40)) {
            char *saved = obj + 0x34;
            W(obj, 0x34) = position->x;
            W(saved, 4) = position->y;
            W(saved, 8) = position->z;
            if (kind == 23) {
                B(obj, 0x20) = 1;
            }
        } else if (func_02089cc0(effect, 0x80)) {
            B(obj, 0x20) = 1;
        }
    }
    (*(void (**)(char *))(obj + 0x2d4))(obj);
    if (func_ov004_0223f398(manager, kind, (u8) S(obj, 0x172))) {
        copy(&origin, position);
        if (kind == 56) {
            if (func_02055d0c(obj + 0xb0, &matrix, 0)) {
                copy(&temp, (Vec *) &matrix.v[9]);
                func_0203f7d0(&origin, &temp);
            }
            flags = 0x42;
            scale = 0x1200;
        } else {
            switch (kind) {
                case 14:
                case 15:
                case 26:
                case 32:
                    flags = 0x82;
                    break;
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 10:
                case 37:
                case 51:
                    if (S(obj, 0x172) != 0) {
                        flags = 0x82;
                        break;
                    }
                default:
                    flags = 0x80;
                    break;
            }
            scale = data_ov004_0225630a[kind * 2];
        }
        func_02031288(obj + 0x68, position, &previous, S(obj, 0x192), data_ov004_0225630a[kind * 2], 0, 11);
        func_02089bec(effect, &origin, data_ov004_0225630a[kind * 2], scale, flags, 0xc0, 0, 0xff, 0x1000);
        func_02089fc8(effect);
    }
    if (data_ov004_02256308[kind * 4] == 0) {
        func_02055124(obj + 0xb0);
        if (kind == 24) {
            func_02056ffc(obj);
            **(int **) (obj + 0x18) = W(obj, 8);
        }
    }
    if (func_ov004_02244ae4((signed char) kind, 0) > 0) {
        copy(&emitPosition, position);
        func_020042c0(obj + 0x24, &emitPosition);
    }
    heading = func_0203f8d0(&translated, (Vec *) (obj + 0x2c8));
    func_020e96c8(&data_021fbe48, translated.x, translated.y, translated.z);
    func_020e9774(&data_021fbe48, (short) (heading + S(obj, 0x190)));
    func_020e9744(&data_021fbe48, S(obj, 0x192));
    func_020e9714(&data_021fbe48, S(obj, 0x194));
    *(Mat *) (obj + 0x114) = data_021fbe48;
}
