/* func_ov054_02260448 @ 0x02260448, 0x2c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov054_02263094;
extern void func_ov054_02261f98(void *);
extern void func_0202ee5c(void *);
extern void func_020edf54(void *);

typedef struct UnkStruct_02260448 {
    void *vtable;
    char pad_04[0x654];
    char sub[1];
} UnkStruct_02260448;

void *func_ov054_02260448(void *self)
{
    UnkStruct_02260448 *s;
    s = (UnkStruct_02260448 *) self;
    s->vtable = &data_ov054_02263094;
    func_ov054_02261f98(s->sub);
    func_0202ee5c(s);
    func_020edf54(s);
    return s;
}
