/* text_base: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a88ec @ 0x020a88ec, 0x24 bytes, Thumb
 * func_020a88c8 @ 0x020a88c8, 0x24 bytes, Thumb
 * func_020a88a0 @ 0x020a88a0, 0x28 bytes, Thumb
 * func_020a887c @ 0x020a887c, 0x24 bytes, Thumb
 * func_020a8874 @ 0x020a8874, 0x8 bytes, Thumb
 */

typedef struct {
    void *vtbl;
    char sub[1];
} Object;

typedef struct {
    void *vtable;
    int sub;
} UnkStruct_020a88a0;

extern void func_020a9b50(void *);
extern void func_020a9b44(void *ptr);
extern char data_020e3d7c[];
extern char data_020da6c4[];
extern void func_020edb3c(void *);
extern int func_02051908(void *, const void *, int);

void *func_020a88ec(void *p)
{
    volatile unsigned int *pp = (volatile unsigned int *) p;
    *pp = (unsigned int) ((char *) data_020da6c4);
    *pp = (unsigned int) ((char *) data_020e3d7c);
    func_020a9b50((char *) p + 4);
    return p;
}

void *func_020a88c8(Object *obj)
{
    obj->vtbl = data_020e3d7c;
    func_020a9b44(&obj->sub);
    obj->vtbl = data_020da6c4;
    return obj;
}

void *func_020a88a0(UnkStruct_020a88a0 *self)
{
    self->vtable = ((char *) data_020e3d7c);
    func_020a9b44(&self->sub);
    self->vtable = ((char *) data_020da6c4);
    func_020edb3c(self);
    return self;
}

void *func_020a887c(void *self)
{
    *(unsigned int *) self = (unsigned int) ((unsigned int *) data_020e3d7c);
    func_020a9b44((char *) self + 4);
    *(unsigned int *) self = (unsigned int) ((unsigned int *) data_020da6c4);
    return self;
}

void func_020a8874(void *argument0, const void *argument1, int argument2)
{
    func_02051908((void *) argument0, (const void *) argument1, (int) argument2);
}
