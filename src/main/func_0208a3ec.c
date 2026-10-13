/* func_0208a3ec @ 0x0208a3ec, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f4(void *p);
extern void func_0208af00(void *p);
extern void func_020edb3c(void *p);
extern unsigned char data_020e2058[];

void *func_0208a3ec(void *arg)
{
    struct UnkStruct_0208a3ec {
        void *field0;
        char pad1[8];
        char fieldC[20];
        char field20[4];
    } *self;

    self = (struct UnkStruct_0208a3ec *) arg;
    self->field0 = (void *) &data_020e2058;
    func_0208a1f4(self->field20);
    func_0208a1f4(self->fieldC);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}
