/* mystery_cat_talk_2: 3 functions, module ov074
 * mwccarm 1.2/base -O4,s
 * func_ov074_02278ffc @ 0x02278ffc, 0x18 bytes, Thumb
 * func_ov074_02278fe4 @ 0x02278fe4, 0x18 bytes, Thumb
 * func_ov074_02278fc4 @ 0x02278fc4, 0x20 bytes, Thumb
 */

extern void *func_0202eb70(void *);
extern void *func_0202eb20(void *p);
extern char data_ov074_02279bd8[];
extern void func_020edb3c(void *self);

void *func_ov074_02278ffc(void *self)
{
    func_0202eb70(self);
    *(void **) self = (void *) ((int *) data_ov074_02279bd8);
    return self;
}

void *func_ov074_02278fe4(void *p)
{
    *(void **) p = ((char *) data_ov074_02279bd8);
    func_0202eb20(p);
    return p;
}

void *func_ov074_02278fc4(void *self)
{
    struct UnkStruct_02278fc4 {
        void *field;
    } *obj = self;
    obj->field = data_ov074_02279bd8;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
