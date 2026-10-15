/* func_0209fb74 @ 0x0209fb74, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3ae8;
extern char data_020da13c;
extern void *func_020a256c(void *ptr);
extern void func_020ee62c(void *ptr);

typedef struct UnkStruct_0209fb74 {
    void *vtable;
} UnkStruct_0209fb74;

UnkStruct_0209fb74 *func_0209fb74(UnkStruct_0209fb74 *s)
{
    s->vtable = &data_020e3ae8;
    func_020a256c((char *) s + 0x54);
    s->vtable = &data_020da13c;
    func_020ee62c(s);
    return s;
}
