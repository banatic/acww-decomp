/* func_ov047_02261978 @ 0x02261978, 0x18 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov047_02262c14;
extern void func_0202eb20(void *self, unsigned int *data);

struct obj_ov047 {
    unsigned int *data;
};

void *func_ov047_02261978(struct obj_ov047 *self)
{
    self->data = &data_ov047_02262c14;
    func_0202eb20(self, &data_ov047_02262c14);
    return self;
}
