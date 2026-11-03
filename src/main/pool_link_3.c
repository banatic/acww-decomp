/* pool_link_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082d1c @ 0x02082d1c, 0x18 bytes, Thumb
 * func_02082d04 @ 0x02082d04, 0x18 bytes, Thumb
 * func_02082ce4 @ 0x02082ce4, 0x20 bytes, Thumb
 */

extern void func_02083100(void *);
extern void func_020830d0(void *);
extern void func_020edb3c(void *self);
extern unsigned char data_020e1a40[];

void *func_02082d1c(void *ptr)
{
    func_02083100(ptr);
    *(unsigned int *) ptr = (unsigned int) ((int *) data_020e1a40);
    return ptr;
}

void *func_02082d04(void *self)
{
    *(void **) self = ((char *) data_020e1a40);
    func_020830d0(self);
    return self;
}

void *func_02082ce4(void *self)
{
    *(void **) self = (void *) data_020e1a40;
    func_020830d0(self);
    func_020edb3c(self);
    return self;
}
