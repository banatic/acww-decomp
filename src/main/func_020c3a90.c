/* func_020c3a90 @ 0x020c3a90, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e877c;
extern void func_020c3c64(void *p);
extern void func_0202ee5c(void *p);
extern void func_020edf54(void *p);

struct UnkStruct_020c3a90 {
    char pad_00;
};

struct UnkStruct_020c3a90_2 {
    void *vtable;
    char pad_04[0x654];
    struct UnkStruct_020c3a90 sub;
};

void *func_020c3a90(void *p)
{
    struct UnkStruct_020c3a90_2 *s = (struct UnkStruct_020c3a90_2 *) p;
    s->vtable = &data_020e877c;
    func_020c3c64(&s->sub);
    func_0202ee5c(p);
    func_020edf54(p);
    return p;
}
