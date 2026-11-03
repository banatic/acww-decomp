/* pool_link_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082e04 @ 0x02082e04, 0x18 bytes, Thumb
 * func_02082dec @ 0x02082dec, 0x18 bytes, Thumb
 * func_02082dcc @ 0x02082dcc, 0x20 bytes, Thumb
 */

extern void func_02083100(void *obj);
extern char data_020e1a68;
extern void func_020830d0(void *arg);
extern void func_020edb3c(void *obj);

void *func_02082e04(void *obj)
{
    func_02083100(obj);
    *(void **) obj = &data_020e1a68;
    return obj;
}

void *func_02082dec(void *ptr)
{
    *(unsigned int *) ptr = (unsigned int) ((unsigned int *) &data_020e1a68);
    func_020830d0(ptr);
    return ptr;
}

void *func_02082dcc(void *obj)
{
    *(void **) obj = (void *) &data_020e1a68;
    func_020830d0(obj);
    func_020edb3c(obj);
    return obj;
}
