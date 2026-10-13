/* func_020a56d4 @ 0x020a56d4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void func_020ee660(void *obj);
extern int data_020da13c;
extern int data_020e3c94;

typedef struct {
    void *volatile vtbl;
    unsigned char pad_04[15];
    volatile unsigned char flags;
} UnkStruct_020a56d4;

void *func_020a56d4(void)
{
    UnkStruct_020a56d4 *p = (UnkStruct_020a56d4 *) func_020edf70(0x50);
    if (p) {
        func_020ee660(p);
        p->vtbl = (void *) &data_020da13c;
        p->vtbl = (void *) &data_020e3c94;
        p->flags |= 1;
        p->flags |= 4;
    }
    return p;
}
