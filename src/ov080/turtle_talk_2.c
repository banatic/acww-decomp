/* turtle_talk_2: 3 functions, module ov080
 * mwccarm 1.2/base -O4,s
 * func_ov080_02278e48 @ 0x02278e48, 0x18 bytes, Thumb
 * func_ov080_02278e30 @ 0x02278e30, 0x18 bytes, Thumb
 * func_ov080_02278e10 @ 0x02278e10, 0x20 bytes, Thumb
 */

struct UnkStruct_02278e48 {
    void *vtable;
};

extern void *func_0202eb70(void *self);
extern char data_ov080_0227925c[];
extern void *func_0202eb20(int *a);
extern void func_020edb3c(void *a);

struct UnkStruct_02278e48 *func_ov080_02278e48(struct UnkStruct_02278e48 *self)
{
    func_0202eb70(self);
    self->vtable = data_ov080_0227925c;
    return self;
}

int *func_ov080_02278e30(int *p)
{
    *p = (int) ((int *) data_ov080_0227925c);
    func_0202eb20(p);
    return p;
}

void *func_ov080_02278e10(void *obj)
{
    void *data = (void *) ((unsigned char *) data_ov080_0227925c);
    *(void **) obj = data;
    func_0202eb20((int *) obj);
    func_020edb3c(obj);
    return obj;
}
