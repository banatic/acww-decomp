/* vram_region_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02055cf4 @ 0x02055cf4, 0x18 bytes, Thumb
 * func_02055ce8 @ 0x02055ce8, 0xc bytes, Thumb
 * func_02055cd0 @ 0x02055cd0, 0x18 bytes, Thumb
 */

struct UnkStruct_02055cd0 {
    void *vtable;
};

extern void func_02055b40(void *arg);
extern void func_020edb3c(void *this);
extern unsigned char data_020dd12c[];

void *func_02055cf4(void *arg)
{
    void *self = arg;
    *(void **) self = ((char *) data_020dd12c);
    func_02055b40(self);
    return self;
}

void func_02055ce8(int *p)
{
    *p = (int) ((char *) data_020dd12c);
}

struct UnkStruct_02055cd0 *func_02055cd0(struct UnkStruct_02055cd0 *this)
{
    this->vtable = (void *) data_020dd12c;
    func_020edb3c(this);
    return this;
}
