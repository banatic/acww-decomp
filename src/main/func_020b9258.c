/* func_020b9258 @ 0x020b9258, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *obj);
extern void func_020edf54(void *obj);

typedef struct {
    volatile int v;
} UnkStruct_020b9258;

extern unsigned char data_020da13c[];
extern unsigned char data_020e587c[];

UnkStruct_020b9258 *func_020b9258(UnkStruct_020b9258 *obj)
{
    obj->v = (unsigned int) data_020e587c;
    obj->v = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}
