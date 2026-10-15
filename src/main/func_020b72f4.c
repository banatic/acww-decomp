/* func_020b72f4 @ 0x020b72f4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *);

typedef struct {
    volatile void *func;
    unsigned char pad_04[15];
    volatile unsigned char flags;
} UnkStruct_020b72f4;

extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5764[];

UnkStruct_020b72f4 *func_020b72f4(void)
{
    UnkStruct_020b72f4 *obj = (UnkStruct_020b72f4 *) func_020edf70(0x50);
    if (obj) {
        func_020ee660(obj);
        obj->func = (void *) data_020da13c;
        obj->func = (void *) data_020e3c94;
        obj->flags |= 1;
        obj->flags |= 4;
        obj->func = (void *) data_020e5764;
    }
    return obj;
}
