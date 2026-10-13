/* func_ov003_0223652c @ 0x0223652c, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    volatile int v;
} UnkStruct_0223652c;
extern void func_020ee660(void *obj);

extern unsigned char data_020da13c[];
extern unsigned char data_ov003_0223c550[];

UnkStruct_0223652c *func_ov003_0223652c(UnkStruct_0223652c *obj)
{
    func_020ee660(obj);
    obj->v = (unsigned int) data_020da13c;
    obj->v = (unsigned int) data_ov003_0223c550;
    return obj;
}
