/* func_020f2980 @ 0x020f2980, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213ee48;
extern void *func_020f4514(void *obj);

void *func_020f2980(void *obj)
{
    void *self = obj;
    void *vt = (void *) &data_0213ee48;

    *(void **) self = vt;
    func_020f4514(self);
    return self;
}
