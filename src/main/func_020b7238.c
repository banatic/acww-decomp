/* func_020b7238 @ 0x020b7238, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *obj);

typedef struct UnkStruct_020b7238 {
    void *vtable;
    char pad_04[15];
    unsigned char flags;
} UnkStruct_020b7238;

extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5574[];

void *func_020b7238(void)
{
    UnkStruct_020b7238 *obj;
    obj = func_020edf70(0x50);
    if (obj) {
        func_020ee660(obj);
        obj->vtable = (void *) data_020da13c;
        obj->vtable = (void *) data_020e3c94;
        obj->flags |= 1;
        obj->flags |= 4;
        obj->vtable = (void *) data_020e5574;
    }
    return obj;
}
