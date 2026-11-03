/* event_announce_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02041a84 @ 0x02041a84, 0x18 bytes, Thumb
 * func_02041a5c @ 0x02041a5c, 0x28 bytes, Thumb
 * func_02041a30 @ 0x02041a30, 0x2c bytes, Thumb
 * func_02041a00 @ 0x02041a00, 0x30 bytes, Thumb
 */

typedef struct {
    void *vtable;
    char pad_04[0x50];
    char unk_54;
} UnkStruct_02041a30;

extern int func_020edf70(int);
extern void *func_020ee660(void *);
extern void *func_02066a04(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020db71c[];
extern void func_020ee62c(void *object);
extern void *func_020669e0(void *);
extern void func_020edf54(void *ptr);

void *func_02041a5c(void *self);

void func_02041a84(void)
{
    int result;

    result = func_020edf70(0x9c);
    if (result != 0) {
        func_02041a5c((void *) result);
    }
}

void *func_02041a5c(void *self)
{
    volatile unsigned int *p_field;
    p_field = (volatile unsigned int *) self;
    func_020ee660(self);
    *p_field = (unsigned int) data_020da13c;
    *p_field = (unsigned int) data_020db71c;
    func_02066a04((char *) self + 0x54);
    return self;
}

void *func_02041a30(UnkStruct_02041a30 *self)
{
    self->vtable = ((char *) data_020db71c);
    func_020669e0(&self->unk_54);
    self->vtable = ((char *) data_020da13c);
    func_020ee62c(self);
    return self;
}

void *func_02041a00(void *arg)
{
    char *this = arg;

    *(void **) this = ((char *) data_020db71c);
    func_020669e0(this + 0x54);
    *(void **) this = ((char *) data_020da13c);
    func_020ee62c(this);
    func_020edf54(this);

    return this;
}
