/* field_actor_23: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02211d4c @ 0x02211d4c, 0x52 bytes, Thumb
 * func_ov003_02211d3c @ 0x02211d3c, 0x10 bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char data[12];
} UnkStruct_02211d4c;

typedef struct {
    char data[16];
} Buf;

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov003_02211da0(void *, int, void *);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

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

void *func_ov003_02211d3c(void *r0, char r1, void *r2)
{
    *(char *) r0 = r1;
    *(int *) ((char *) r0 + 4) = *(int *) r2;
    *(int *) ((char *) r0 + 8) = *(int *) ((char *) r2 + 4);
    *(int *) ((char *) r0 + 12) = *(int *) ((char *) r2 + 8);
    return r0;
}
