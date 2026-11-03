/* sound_source_member: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221ef7c @ 0x0221ef7c, 0x14 bytes, Thumb
 * func_ov003_0221ef78 @ 0x0221ef78, 0x2 bytes, Thumb
 * func_ov003_0221ef70 @ 0x0221ef70, 0x8 bytes, Thumb
 * func_ov003_0221ef44 @ 0x0221ef44, 0x2a bytes, Thumb
 * func_ov003_0221ef3c @ 0x0221ef3c, 0x8 bytes, Thumb
 */

struct Vec3 {
    int x;
    int y;
    int z;
};

extern unsigned char data_0213efe8[];
extern unsigned char data_0213f004[];
extern int func_0200430c(void *argument0);
extern void func_020042c0(void *a, struct Vec3 *v);
extern void func_02004290(void *a, void *b);
extern void func_02004280(void *argument0);

extern void func_ov003_0221ef7c(volatile unsigned int *p)
{
    *p = (unsigned int) data_0213efe8;
    *p = (unsigned int) data_0213f004;
}

void func_ov003_0221ef78(void *object) {}

void func_ov003_0221ef70(void *argument0)
{
    func_0200430c(argument0);
}

void func_ov003_0221ef44(void *a, struct Vec3 *b, void *c)
{
    struct Vec3 local;

    local.x = b->x;
    local.y = b->y;
    local.z = b->z;
    func_020042c0(a, &local);
    func_02004290(a, c);
}

void func_ov003_0221ef3c(void *argument0)
{
    func_02004280(argument0);
}
