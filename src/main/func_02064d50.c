/* func_02064d50 @ 0x02064d50, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020de710[];
extern char data_020da13c[];
extern void *func_02064d8c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020ee62c(void *self);
extern void func_020edf54(void *self);

struct UnkStruct_02064d50 {
    char data[0x44];
};

struct Main {
    void *vtable;
    char pad_04[0x54];
    struct UnkStruct_02064d50 sub;
};

void *func_02064d50(void *arg)
{
    struct Main *self = (struct Main *) arg;
    self->vtable = (void *) data_020de710;
    __cxa_vec_cleanup((void *) (&self->sub), 3, 0x44, (((void (*)(void *)) func_02064d8c)));
    self->vtable = (void *) data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
