/* func_ov111_0229ef78 @ 0x0229ef78, 0x18 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov111_022a0ff0;
extern void func_020a887c(void *self, char *data);

void *func_ov111_0229ef78(void *self)
{
    *(char **) self = &data_ov111_022a0ff0;
    func_020a887c(self, &data_ov111_022a0ff0);
    return self;
}
