/* func_ov004_0223db08 @ 0x0223db08, 0x160 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern "C" void *func_02032c64(void *);
extern "C" void *func_02032c50(void *);
extern "C" int func_02034270(void *, Vec *, int, int);
extern "C" void func_0203423c(void *);
extern "C" int func_020341c8(void *, int);
extern "C" void func_02031288(void *, Vec *, void *, int, int, void *, int);
static inline int hit_count(void *p)
{
    return ((unsigned char *) p)[16];
}
extern "C" unsigned char func_ov004_0223db08(char *self)
{
    unsigned char result = 0;
    Vec *position = (Vec *) (self + 0x230);
    // The three query objects occupy consecutive ROM frame ranges.
    struct {
        int collision[12];
        int first[16];
        int second[16];
    } frame;
    short angle, hit;
    func_02032c64(frame.collision);
    func_02034270(frame.first, position, 0, 0);
    angle = *(short *) (self + 0x8e);
    if (*(int *) (self + 0x248) == 0 || *(int *) (self + 0x250) == 0) {
        *(int *) (self + 0x248) = *(int *) (self + 0x230);
        *(int *) (self + 0x24c) = *(int *) (self + 0x234);
        *(int *) (self + 0x250) = *(int *) (self + 0x238);
    }
    func_02031288(frame.collision, position, self + 0x248, angle, 0x19a, self, 15);
    hit = hit_count(frame.collision);
    if (func_020341c8(frame.first, 1) > 0x200 || position->y > 0x1000 || hit > 0) {
        ++result;
    }
    func_02034270(frame.second, position + 1, 0, 0);
    if (*(int *) (self + 0x254) == 0 || *(int *) (self + 0x25c) == 0) {
        *(int *) (self + 0x254) = *(int *) (self + 0x23c);
        *(int *) (self + 0x258) = *(int *) (self + 0x240);
        *(int *) (self + 0x25c) = *(int *) (self + 0x244);
    }
    func_02031288(frame.collision, position + 1, self + 0x254, angle, 0x19a, self, 15);
    hit = hit_count(frame.collision);
    if (func_020341c8(frame.second, 1) > 0x200 || position[1].y > 0x1000 || hit > 0) {
        result += 2;
    }
    func_0203423c(frame.second);
    func_0203423c(frame.first);
    func_02032c50(frame.collision);
    return result;
}
