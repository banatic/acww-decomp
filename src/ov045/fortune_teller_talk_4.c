/* fortune_teller_talk_4: 4 functions, module ov045
 * mwccarm 1.2/base -O4,s
 * func_ov045_02260d4c @ 0x02260d4c, 0x18 bytes, Thumb
 * func_ov045_02260d34 @ 0x02260d34, 0x18 bytes, Thumb
 * func_ov045_02260d14 @ 0x02260d14, 0x20 bytes, Thumb
 * func_ov045_02260cb0 @ 0x02260cb0, 0x64 bytes, Thumb
 */

struct UnkStruct_02260d4c {
    void *vtable;
};

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned int unk_B4;
} UnkStruct_02260cb0;

extern void *func_020161ac(void *self);
extern char data_ov045_02261460;
extern void *func_0201615c(void *);
extern void func_020edb3c(void *);
extern int func_02019df8(unsigned int);
extern int func_02019e00(unsigned int);
extern void func_02035624(int);
extern int func_02016014(void *, int);
extern int func_ov004_02230518(void);
extern int func_ov004_022304f8(void);
extern int func_ov004_022304d8(void);

struct UnkStruct_02260d4c *func_ov045_02260d4c(struct UnkStruct_02260d4c *self)
{
    func_020161ac(self);
    self->vtable = &data_ov045_02261460;
    return self;
}

void *func_ov045_02260d34(void *self)
{
    *(void **) self = (void *) &data_ov045_02261460;
    func_0201615c(self);
    return self;
}

void *func_ov045_02260d14(void *obj)
{
    *(void **) obj = (void *) &data_ov045_02261460;
    func_0201615c(obj);
    func_020edb3c(obj);
    return obj;
}

void func_ov045_02260cb0(UnkStruct_02260cb0 *self, int key)
{
    if (key == func_02019df8(self->unk_B4 + 0x564) && func_02019e00(self->unk_B4 + 0x564) == 8) {
    } else {
        switch (key) {
            case 0x1e:
                func_ov004_02230518();
                break;
            case 0x1f:
                func_02035624(0x10);
                func_ov004_022304f8();
                break;
            case 0x20:
                func_ov004_022304d8();
                break;
        }
    }
    func_02016014(self, key);
}
