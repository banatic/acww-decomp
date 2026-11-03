/* house_visitor: 6 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022752d8 @ 0x022752d8, 0xc bytes, Thumb
 * func_ov068_022752c4 @ 0x022752c4, 0x14 bytes, Thumb
 * func_ov068_022752ac @ 0x022752ac, 0x18 bytes, Thumb
 * func_ov068_02275278 @ 0x02275278, 0x34 bytes, Thumb
 * func_ov068_02275248 @ 0x02275248, 0x30 bytes, Thumb
 * func_ov068_02275228 @ 0x02275228, 0x20 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    char pad_04[0x89c - 4];
    void *unk_89C;
} UnkStruct_02275248;

extern void *func_0202de4c(void *p);
extern unsigned char data_ov068_022780b0[];
extern void *func_0202e5e0(void *);
extern void func_020edf54(void *);
extern unsigned char data_ov068_02278140[];
extern void func_020edb3c(void *param);

void func_ov068_022752d8(unsigned char *r0)
{
    r0[0x897] = 1;
}

int func_ov068_022752c4(unsigned char *p)
{
    if (p[0x897] != 0) {
        return 0;
    }
    return 1;
}

void *func_ov068_022752ac(void *self)
{
    *(void **) self = (void *) data_ov068_022780b0;
    func_0202de4c(self);
    return self;
}

void *func_ov068_02275278(void *this)
{
    ((int *) this)[0] = (int) (unsigned int) data_ov068_02278140;
    *((int *) ((char *) this + 0x89c)) = (int) (unsigned int) data_ov068_022780b0;
    func_0202de4c((char *) this + 0x89c);
    func_0202e5e0(this);
    func_020edf54(this);
    return this;
}

void *func_ov068_02275248(UnkStruct_02275248 *obj)
{
    obj->unk_00 = ((char *) data_ov068_02278140);
    obj->unk_89C = ((char *) data_ov068_022780b0);
    func_0202de4c((void *) &obj->unk_89C);
    func_0202e5e0(obj);
    return obj;
}

void *func_ov068_02275228(void *self)
{
    *(void **) self = (void *) ((int *) data_ov068_022780b0);
    func_0202de4c(self);
    func_020edb3c(self);
    return self;
}
