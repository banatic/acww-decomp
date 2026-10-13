/* func_ov090_02298f48 @ 0x02298f48, 0x2c bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov090_02299820;
void func_ov002_0220ba0c(void *);
void func_ov002_0220826c(void *);
void func_ov002_02207f6c(void *);

void *func_ov090_02298f48(void *self)
{
    *(void **) self = &data_ov090_02299820;
    func_ov002_0220ba0c((char *) self + 0x1164);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
