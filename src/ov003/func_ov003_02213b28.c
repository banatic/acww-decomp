/* func_ov003_02213b28 @ 0x02213b28, 0xc8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073908(int, int);
extern void func_ov003_022145a0(void *);
extern void func_ov003_02214384(void *);
extern void func_ov003_022145b0(void *);
extern int func_0201100c(void *);
extern void func_02010d64(void *);
extern void func_ov003_02213cd0(void *);
extern void func_ov003_02213bf0(void *);
extern void func_ov003_02214568(void *);
extern void func_ov003_02213d18(void *);
extern int func_0200f554(void *);
extern int func_0203f7d0(void *, void *);

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    int pad_00;
    int pad_04;
    Vec3 vec;
} DstStruct;

void func_ov003_02213b28(unsigned char *self)
{
    Vec3 tmp, src;
    DstStruct *dst;
    int tx, ty, tz;

    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_ov003_022145a0(self);
        func_ov003_02214384(self);
        func_ov003_022145b0(self);
        func_0201100c(self);
        func_02010d64(self);
        func_ov003_02213cd0(self);
        func_ov003_02213bf0(self);
        func_ov003_02214568(self);
    } else {
        func_ov003_02213d18(self);
        func_ov003_022145b0(self);
        if (func_0200f554(self) != 0) {
            func_0201100c(self);
        }
        func_02010d64(self);
        func_ov003_02213cd0(self);
        func_ov003_02213bf0(self);
        func_ov003_02214568(self);
    }

    dst = (DstStruct *) (self + 0x7d4);
    tz = *(int *) (self + 0x634);
    ty = *(int *) (self + 0x630);
    tx = *(int *) (self + 0x62c);
    src.x = tx;
    src.y = ty;
    src.z = tz;
    func_0203f7d0(&tmp, &src);
    dst->vec.x = tmp.x;
    dst->vec.y = tmp.y;
    dst->vec.z = tmp.z;
}