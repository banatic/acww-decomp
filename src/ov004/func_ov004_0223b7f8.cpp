/* func_ov004_0223b7f8 @ 0x0223b7f8, 0x160 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short x, y;
} Cell;
typedef struct {
    int a, b;
} Shape;
extern "C" int func_020538dc(int);
extern "C" int func_02053be0(int);
extern "C" int func_0205395c(int);
extern "C" unsigned short func_0204bc50(int, int);
extern "C" Shape *func_02052e3c(Shape *, unsigned short *);
extern "C" Cell *func_02052dc0(Shape *, unsigned int);
extern "C" unsigned int func_02052e20(Shape *);
extern "C" void func_02052e38(Shape *);
extern "C" void *data_021c80bc;
extern "C" unsigned short *func_0204f5e0(void *, unsigned int, unsigned int, int, int, unsigned char);
extern "C" int func_02031b38(int, int);
extern "C" void *func_ov004_0223cd50(void);
extern "C" char *func_ov004_0223cc10(void *, int, int, int);
extern "C" int func_ov004_0220ce04(char *);
extern "C" unsigned int func_ov004_02211394(int, int, int, int, unsigned char, int);
extern "C" int func_ov004_0223b7f8(unsigned int *out, int x, int y, int rotation, int item, unsigned char layer, int blockedX,
                                   int blockedY)
{
    int special = func_020538dc(item);
    int category = func_02053be0(item);
    int type = func_0205395c(item);
    unsigned short encoded = func_0204bc50(item, rotation);
    Shape shape;
    func_02052e3c(&shape, &encoded);
    int ty;
    void *map = data_021c80bc;
    int valid = 1;
    unsigned int i;
    for (i = 0; i < func_02052e20(&shape); ++i) {
        int tx = x + func_02052dc0(&shape, i)->x;
        ty = y + func_02052dc0(&shape, i)->y;
        int ax = tx >> 4, ay = ty >> 4;
        unsigned short *slot = func_0204f5e0(map, ax, ay, tx - (ax << 4), ty - (ay << 4), layer);
        if (!special && tx == blockedX && ty == blockedY) {
            valid = 0;
            break;
        }
        if (!slot) {
            valid = 0;
            break;
        }
        if (*slot != 0xfff1) {
            valid = 0;
            break;
        }
        if (!func_02031b38(tx, ty)) {
            valid = 0;
            break;
        }
        if (layer == 1) {
            if (category) {
                valid = 0;
                break;
            }
            if (type != 2) {
                valid = 0;
                break;
            }
            char *object = func_ov004_0223cc10(func_ov004_0223cd50(), tx, ty, 0);
            if (!object || (object && *(int *) (object + 0x788) != 1) || (object && func_ov004_0220ce04(object))) {
                valid = 0;
                break;
            }
        }
    }
    if (valid) {
        *out = func_ov004_02211394(x, y, item, rotation, layer, 1);
        func_02052e38(&shape);
        return 3;
    }
    func_02052e38(&shape);
    return 2;
}
