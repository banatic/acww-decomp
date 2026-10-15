/* func_020a9c4c @ 0x020a9c4c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee660(void *);

typedef struct {
    volatile unsigned int vtbl;
} UnkStruct_020a9c4c;

extern unsigned char data_020da13c[];
extern unsigned char data_020e3e8c[];

UnkStruct_020a9c4c *func_020a9c4c(UnkStruct_020a9c4c *obj)
{
    func_020ee660(obj);
    obj->vtbl = (unsigned int) data_020da13c;
    obj->vtbl = (unsigned int) data_020e3e8c;
    return obj;
}
