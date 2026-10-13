/* func_ov053_0226164c @ 0x0226164c, 0x5c bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov053_02260bb8(void *, void *);
extern void func_0201c3f4(void *, int);
extern void func_0201af28(void *, int, int, int, int);

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0226164c;

extern UnkStruct_0226164c data_ov053_022617e0;

int func_ov053_0226164c(void *self)
{
    if (!func_0202edc8(self)) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov053_02260bb8((char *) self + 0x658, self);
    func_0201c3f4(self, 0x100);
    func_0201af28((char *) self + 0x350, 2, data_ov053_022617e0.a, data_ov053_022617e0.b, data_ov053_022617e0.c);
    return 1;
}
