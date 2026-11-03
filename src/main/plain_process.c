/* plain_process: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b9258 @ 0x020b9258, 0x28 bytes, Thumb
 * func_020b9238 @ 0x020b9238, 0x20 bytes, Thumb
 * func_020b920c @ 0x020b920c, 0x2c bytes, Thumb
 */

typedef struct {
    volatile int v;
} UnkStruct_020b9258;

extern void func_020ee62c(void *obj);
extern void func_020edf54(void *obj);
extern unsigned char data_020da13c[];
extern unsigned char data_020e587c[];
extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *ptr);

UnkStruct_020b9258 *func_020b9258(UnkStruct_020b9258 *obj)
{
    obj->v = (unsigned int) data_020e587c;
    obj->v = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}

volatile unsigned int *func_020b9238(volatile unsigned int *p)
{
    unsigned int val;
    *p = (unsigned int) ((int *) data_020e587c);
    val = (unsigned int) ((int *) data_020da13c);
    *p = val;
    func_020ee62c((void *) p);
    return p;
}

void *func_020b920c(void)
{
    void *p;
    p = func_020edf70(0x50);
    if (p) {
        func_020ee660(p);
        *(volatile unsigned int *) p = (unsigned int) (unsigned int) data_020da13c;
        *(volatile unsigned int *) p = (unsigned int) (unsigned int) data_020e587c;
    }
    return p;
}
