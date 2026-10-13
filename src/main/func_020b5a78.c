/* func_020b5a78 @ 0x020b5a78, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void func_020ee660(void *ptr);
extern int data_020da13c;
extern int data_020e3c94;
extern int data_020e5320;

struct UnkStruct_020b5a78 {
    void *p;
    unsigned char pad_04[15];
    unsigned char flags;
};

void *func_020b5a78(void)
{
    volatile struct UnkStruct_020b5a78 *obj = (volatile struct UnkStruct_020b5a78 *) func_020edf70(0x6c);
    if (obj) {
        func_020ee660((void *) obj);
        obj->p = (void *) &data_020da13c;
        obj->p = (void *) &data_020e3c94;
        obj->flags |= 1;
        obj->flags |= 4;
        obj->p = (void *) &data_020e5320;
    }
    return (void *) obj;
}
