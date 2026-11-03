/* sound_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02004150 @ 0x02004150, 0x8 bytes, Thumb
 * func_02004148 @ 0x02004148, 0x8 bytes, Thumb
 * func_02004140 @ 0x02004140, 0x8 bytes, Thumb
 * func_02004138 @ 0x02004138, 0x8 bytes, Thumb
 * func_02004130 @ 0x02004130, 0x8 bytes, Thumb
 * func_02004128 @ 0x02004128, 0x8 bytes, Thumb
 * func_02004120 @ 0x02004120, 0x8 bytes, Thumb
 * func_02004118 @ 0x02004118, 0x8 bytes, Thumb
 * func_02004110 @ 0x02004110, 0x8 bytes, Thumb
 * func_02004108 @ 0x02004108, 0x8 bytes, Thumb
 * func_020040bc @ 0x020040bc, 0x4c bytes, Thumb
 */

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_020040bc;

extern void func_020f67e4(void *, unsigned int);
extern void func_020f66f0(void *);
extern void func_020f65fc(void *, int);
extern int func_020f65d0(void *);
extern unsigned char func_020f65c8(void *);
extern int func_020f6754(void *, unsigned int);
extern void *func_020f6720(unsigned char *);
extern void *func_020f6970(void);
extern void func_020fa054(void *, unsigned short);
extern void func_020f9fcc(void *, int);
extern int data_021c67a4;
extern UnkStruct_020040bc data_021c67b8;
extern int func_020f9ea4(void *self, UnkStruct_020040bc *v);

void func_02004150(void *argument0, unsigned int argument1)
{
    func_020f67e4((void *) argument0, (unsigned int) argument1);
}

void func_02004148(void *argument0)
{
    func_020f66f0((void *) argument0);
}

void func_02004140(void *argument0, int argument1)
{
    func_020f65fc((void *) argument0, (int) argument1);
}

int func_02004138(void *argument0)
{
    return func_020f65d0((void *) argument0);
}

unsigned char func_02004130(void *argument0)
{
    return func_020f65c8((void *) argument0);
}

int func_02004128(void *argument0, unsigned int argument1)
{
    return func_020f6754((void *) argument0, (unsigned int) argument1);
}

void *func_02004120(unsigned char *argument0)
{
    return func_020f6720((unsigned char *) argument0);
}

void *func_02004118(void *object)
{
    return func_020f6970();
}

void func_02004110(void *argument0, unsigned short argument1)
{
    func_020fa054((void *) argument0, (unsigned short) argument1);
}

void func_02004108(void *argument0, int argument1)
{
    func_020f9fcc((void *) argument0, (int) argument1);
}

int func_020040bc(void *self, UnkStruct_020040bc *v)
{
    UnkStruct_020040bc t;
    if (v != 0) {
        if (data_021c67a4 == 0) {
            return -1;
        }
        t.x = v->x - data_021c67b8.x;
        t.y = v->y - data_021c67b8.y;
        t.z = v->z - data_021c67b8.z;
        return func_020f9ea4(self, &t);
    }
    return -1;
}
