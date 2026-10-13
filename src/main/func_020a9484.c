/* func_020a9484 @ 0x020a9484, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3e24;
extern void func_020a9c84(void *);

typedef struct {
    char *data;
    int value;
    char sub;
} UnkStruct_020a9484;

UnkStruct_020a9484 *func_020a9484(UnkStruct_020a9484 *self)
{
    self->data = &data_020e3e24;
    self->value = 0;
    func_020a9c84(&self->sub);
    return self;
}
