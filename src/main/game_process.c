/* game_process: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202f144 @ 0x0202f144, 0x20 bytes, Thumb
 * func_0202f134 @ 0x0202f134, 0xe bytes, Thumb
 * func_0202f12c @ 0x0202f12c, 0x8 bytes, Thumb
 * func_0202f10c @ 0x0202f10c, 0x20 bytes, Thumb
 * func_0202f0f4 @ 0x0202f0f4, 0x18 bytes, Thumb
 */

struct UnkStruct_0202f0f4 {
    void *vtable;
};

extern void func_020ee470(int a);
extern void func_020ee59c(int a, int b);
extern int func_020edbbc(int a, int b, int c, int d);
extern int func_020edba4(int, int, int);
extern void func_020ee62c(void *obj);
extern void func_020edf54(void *obj);
extern unsigned char data_020da13c[];

void func_0202f144(int a, int b)
{
    if (b == 1) {
        func_020ee470(a);
    }
    func_020ee59c(a, b);
}

int func_0202f134(int a, int b, int c, int d)
{
    return func_020edbbc(a, b, c, d);
}

int func_0202f12c(int argument0, int argument1, int argument2)
{
    return func_020edba4((int) argument0, (int) argument1, (int) argument2);
}

void *func_0202f10c(void *obj)
{
    *(unsigned int *) obj = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}

struct UnkStruct_0202f0f4 *func_0202f0f4(struct UnkStruct_0202f0f4 *self)
{
    self->vtable = (void *) data_020da13c;
    func_020ee62c((void *) self);
    return self;
}
