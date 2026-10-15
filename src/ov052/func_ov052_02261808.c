/* func_ov052_02261808 @ 0x02261808, 0xa0 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x8e - 0x60];
    short unk_8E;
} UnkStruct_02261808;

extern Vec3 *func_02095794(int);
extern int func_0201c378(UnkStruct_02261808 *, int);
extern int func_0201c2c8(UnkStruct_02261808 *, int);
extern int func_020e8b4c(int, int);
extern void func_0201b458(Vec3 *, UnkStruct_02261808 *, Vec3 *);
extern int func_020eaa2c(Vec3 *, void *);
extern void func_ov052_02261908(UnkStruct_02261808 *, int);
extern int func_ov052_022604ec(UnkStruct_02261808 *);
extern int func_ov052_022604a0(UnkStruct_02261808 *);
extern int func_ov052_02260554(UnkStruct_02261808 *);

int func_ov052_02261808(UnkStruct_02261808 *self)
{
    Vec3 v1;
    Vec3 v2;
    int a;
    int b;
    int tmp;
    Vec3 *src;

    src = func_02095794(4);
    v1.x = src->x;
    v1.y = src->y;
    v1.z = src->z;
    a = func_0201c378(self, 4);
    tmp = func_0201c2c8(self, 4);
    b = func_020e8b4c(self->unk_8E, tmp);
    func_0201b458(&v2, self, &v1);
    if (a > 0x3000 && func_020eaa2c(&v2, &self->unk_5C) != 0) {
        func_ov052_02261908(self, 3);
    } else if (b > 0x2000) {
        func_ov052_02261908(self, 2);
    }
    if (func_ov052_022604ec(self) != 0) {
        return 1;
    }
    if (func_ov052_022604a0(self) != 0) {
        return 1;
    }
    func_ov052_02260554(self);
    return 1;
}
