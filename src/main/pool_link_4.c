/* pool_link_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082d90 @ 0x02082d90, 0x18 bytes, Thumb
 * func_02082d78 @ 0x02082d78, 0x18 bytes, Thumb
 * func_02082d58 @ 0x02082d58, 0x20 bytes, Thumb
 */

extern void func_02083100(void *);
extern void func_020830d0(void *obj);
extern unsigned int data_020e19dc[];
extern void func_020edb3c(void *);

void *func_02082d90(void *p)
{
    func_02083100(p);
    *(void **) p = (void *) ((char *) data_020e19dc);
    return p;
}

void *func_02082d78(void *obj)
{
    *(void **) obj = data_020e19dc;
    func_020830d0(obj);
    return obj;
}

void *func_02082d58(void *ptr)
{
    *(void **) ptr = (void *) ((char *) data_020e19dc);
    func_020830d0(ptr);
    func_020edb3c(ptr);
    return ptr;
}
