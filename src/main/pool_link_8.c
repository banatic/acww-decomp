/* pool_link_8: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082f60 @ 0x02082f60, 0x18 bytes, Thumb
 * func_02082f48 @ 0x02082f48, 0x18 bytes, Thumb
 * func_02082f28 @ 0x02082f28, 0x20 bytes, Thumb
 */

struct UnkStruct_02082f28 {
    void *ptr;
};

extern void func_02083100(void *);
extern void func_020830d0(void *obj);
extern void func_020edb3c(void *obj);
extern unsigned char data_020e19f0[];

void *func_02082f60(void *ptr)
{
    func_02083100(ptr);
    *(unsigned int *) ptr = (unsigned int) ((unsigned int *) data_020e19f0);
    return ptr;
}

void *func_02082f48(void *this)
{
    *(void **) this = ((void **) data_020e19f0);
    func_020830d0(this);
    return this;
}

void *func_02082f28(void *obj)
{
    struct UnkStruct_02082f28 *self = (struct UnkStruct_02082f28 *) obj;
    self->ptr = (void *) data_020e19f0;
    func_020830d0(obj);
    func_020edb3c(obj);
    return obj;
}
