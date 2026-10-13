/* func_0208e81c @ 0x0208e81c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtbl;
    char pad_04[8];
    int sub1;
    char pad_10[28];
    int sub2;
} UnkStruct_0208e81c;

extern void func_0208a1f4(void *ptr);
extern void func_0208af00(void *self);
extern void func_020edb3c(void *self);

extern unsigned char data_020e2314[];

UnkStruct_0208e81c *func_0208e81c(UnkStruct_0208e81c *self)
{
    self->vtbl = (void *) data_020e2314;
    func_0208a1f4(&self->sub2);
    func_0208a1f4(&self->sub1);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}
