/* func_02082f28 @ 0x02082f28, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020830d0(void *obj);
extern void func_020edb3c(void *obj);

struct UnkStruct_02082f28 {
    void *ptr;
};

extern unsigned char data_020e19f0[];

void *func_02082f28(void *obj)
{
    struct UnkStruct_02082f28 *self = (struct UnkStruct_02082f28 *) obj;
    self->ptr = (void *) data_020e19f0;
    func_020830d0(obj);
    func_020edb3c(obj);
    return obj;
}
