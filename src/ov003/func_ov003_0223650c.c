/* func_ov003_0223650c @ 0x0223650c, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    volatile int v;
} UnkStruct_0223650c;
extern void func_020ee62c(void *obj);

extern unsigned char data_020da13c[];
extern unsigned char data_ov003_0223c550[];

UnkStruct_0223650c *func_ov003_0223650c(UnkStruct_0223650c *obj)
{
    obj->v = (unsigned int) data_ov003_0223c550;
    obj->v = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}
