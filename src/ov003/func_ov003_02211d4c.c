/* func_ov003_02211d4c @ 0x02211d4c, 0x52 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov003_02211da0(void *, int, void *);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char data[12];
} UnkStruct_02211d4c;

typedef struct {
    char data[16];
} Buf;

int func_ov003_02211d4c(void *a, int b, Vec3 *c, int d, short e)
{
    UnkStruct_02211d4c local1;
    Buf local3;
    Vec3 local2;

    func_0200e92c(&local1);
    func_0200e90c(&local1, 0x5e, d, e);
    local2.x = c->x;
    local2.y = c->y;
    local2.z = c->z;
    func_ov003_02211da0(&local3, b, &local2);
    {
        int result = func_0200e894(a, &local1);
        func_0200e91c(&local1);
        return result;
    }
}
