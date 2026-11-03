/* activity: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209fba0 @ 0x0209fba0, 0x30 bytes, Thumb
 * func_0209fb74 @ 0x0209fb74, 0x2c bytes, Thumb
 */

typedef struct UnkStruct_0209fb74 {
    void *vtable;
} UnkStruct_0209fb74;

extern __thumb void *func_020a256c(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern char data_020e3ae8;
extern char data_020da13c;

void *func_0209fba0(void *p)
{
    *(unsigned int *) p = (unsigned int) ((const int *) &data_020e3ae8);
    func_020a256c((char *) p + 0x54);
    *(unsigned int *) p = (unsigned int) ((const int *) &data_020da13c);
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}

UnkStruct_0209fb74 *func_0209fb74(UnkStruct_0209fb74 *s)
{
    s->vtable = &data_020e3ae8;
    func_020a256c((char *) s + 0x54);
    s->vtable = &data_020da13c;
    func_020ee62c(s);
    return s;
}
