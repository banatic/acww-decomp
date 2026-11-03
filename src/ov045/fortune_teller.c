/* fortune_teller: 2 functions, module ov045
 * mwccarm 1.2/base -O4,s
 * func_ov045_02260448 @ 0x02260448, 0x2c bytes, Thumb
 * func_ov045_02260420 @ 0x02260420, 0x28 bytes, Thumb
 */

typedef struct UnkStruct_02260420_2 {
    char pad_00;
} UnkStruct_02260420_2;

typedef struct UnkStruct_02260420 {
    void *vtable;
    unsigned char pad_04[0x688];
    UnkStruct_02260420_2 sub;
} UnkStruct_02260420;

extern char data_ov045_022614f0;
extern void *func_ov045_02260d34(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);

void *func_ov045_02260448(void *obj)
{
    *(void **) obj = &data_ov045_022614f0;
    func_ov045_02260d34((void *) ((char *) obj + 0x68c));
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}

UnkStruct_02260420 *func_ov045_02260420(UnkStruct_02260420 *self)
{
    self->vtable = &data_ov045_022614f0;
    func_ov045_02260d34((void *) (&self->sub));
    func_0202ee5c((void *) self);
    return self;
}
