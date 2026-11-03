/* label_sprite_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208f640 @ 0x0208f640, 0x20 bytes, Thumb
 * func_0208f628 @ 0x0208f628, 0x18 bytes, Thumb
 * func_0208f608 @ 0x0208f608, 0x20 bytes, Thumb
 */

extern void *func_020a8cac(void *p);
extern void func_020a8c1c(void *p);
extern unsigned char data_020e2388;
extern void *func_020a8c38(void *this);
extern void *func_020edb3c(void *) __attribute__((arm));

void *func_0208f640(void *p)
{
    func_020a8cac(p);
    *(void **) p = (void *) &data_020e2388;
    func_020a8c1c(p);
    return p;
}

void *func_0208f628(void *this)
{
    *(void **) this = ((char *) &data_020e2388);
    func_020a8c38(this);
    return this;
}

void *func_0208f608(void *obj)
{
    *(void **) obj = ((int *) &data_020e2388);
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
