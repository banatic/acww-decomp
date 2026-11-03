/* layer_load_task_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b9af4 @ 0x020b9af4, 0x20 bytes, Thumb
 * func_020b9adc @ 0x020b9adc, 0x16 bytes, Thumb
 * func_020b9a90 @ 0x020b9a90, 0x4c bytes, Thumb
 */

typedef struct {
    void *vtable;
    char pad_04[0x20];
    char sub;
} UnkStruct_020b9af4;

extern void *func_020b9d1c(void *);
extern void func_020ba108(void *);
extern unsigned char data_020e5944[];
extern void func_020b9ce4(void *param);
extern int func_020b9c7c(void *p);
extern unsigned int func_020ba0dc(void *p);
extern void func_020ba07c(void *p);

void *func_020b9af4(void *this)
{
    func_020b9d1c(this);
    ((UnkStruct_020b9af4 *) this)->vtable = (void *) data_020e5944;
    func_020ba108(&((UnkStruct_020b9af4 *) this)->sub);
    return this;
}

void func_020b9adc(void *param)
{
    void *r4;
    r4 = param;
    func_020b9ce4(r4);
    r4 = (char *) r4 + 0x24;
    func_020ba108(r4);
}

int func_020b9a90(void *p)
{
    unsigned char *q = (unsigned char *) p;

    if (func_020b9c7c(p) != 0) {
        return 1;
    }

    switch (q[0xe]) {
        case 8:
            func_020ba0dc(q + 0x10);
            q += 0x24;
            func_020ba0dc(q);
            goto success;
        case 9:
            func_020ba0dc(q + 0x10);
            q += 0x24;
            func_020ba07c(q);
            goto success;
        default:
            return 0;
    }

success:
    return 1;
}
