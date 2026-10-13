/* func_02062e50 @ 0x02062e50, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a88ec(void *);
extern void func_0205195c(void *);
extern char data_020de614;

void *func_02062e50(void *self)
{
    func_020a88ec(self);
    *(void **) self = (void *) &data_020de614;
    func_0205195c(self);
    return self;
}
