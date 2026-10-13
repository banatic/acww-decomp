/* func_ov003_022364e4 @ 0x022364e4, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    volatile int v;
} UnkStruct_022364e4;
extern void func_020ee62c(void *obj);
extern void func_020edf54(void *obj);

extern unsigned char data_020da13c[];
extern unsigned char data_ov003_0223c550[];

UnkStruct_022364e4 *func_ov003_022364e4(UnkStruct_022364e4 *obj)
{
    obj->v = (unsigned int) data_ov003_0223c550;
    obj->v = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}
