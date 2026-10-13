/* func_020f3bb8 @ 0x020f3bb8, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f9868(char *);
extern void func_020f4514(void *);
extern int data_0213ea04;

typedef struct UnkStruct_020f3bb8 {
    void *vtbl;
    int unk_04;
    char subobj;
} UnkStruct_020f3bb8;

void *func_020f3bb8(UnkStruct_020f3bb8 *self)
{
    self->vtbl = (void *) &data_0213ea04;
    func_020f9868(&self->subobj);
    func_020f4514(self);
    return self;
}
