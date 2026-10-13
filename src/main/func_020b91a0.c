/* func_020b91a0 @ 0x020b91a0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e5858;
extern void func_0208a1f4(void *p);
extern void func_0208ad24(void *p);

void *func_020b91a0(void *self)
{
    struct {
        void *field_0;
        char pad[0xC8];
        char field_CC;
    } *obj = self;

    obj->field_0 = &data_020e5858;
    func_0208a1f4(&obj->field_CC);
    func_0208ad24(self);
    return self;
}
