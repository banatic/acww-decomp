/* func_02083608 @ 0x02083608, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083ca8(void *obj, int param);
extern void *func_02083654(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_0208366c(void *);

extern unsigned char data_020e1ac8[];

void *func_02083608(void *self)
{
    func_02083ca8(self, 5);
    *((void **) self) = (void *) data_020e1ac8;
    {
        void (*cb)(void *) = (((void (*)(void *)) func_02083654));
        __cxa_vec_ctor((void *) ((char *) self + 8), 5, 8, (((void (*)(void *)) func_0208366c)), cb);
    }
    return self;
}
