/* layer_load_task_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b9d1c @ 0x020b9d1c, 0x20 bytes, Thumb
 * func_020b9cfc @ 0x020b9cfc, 0x20 bytes, Thumb
 * func_020b9ce4 @ 0x020b9ce4, 0x16 bytes, Thumb
 */

typedef struct UnkStruct_020b9cfc {
    void *vtable;
    unsigned char pad_04[0xc];
    unsigned char sub[1];
} UnkStruct_020b9cfc;

extern void func_020ba1cc(void *);
extern void func_020ba108(void *);
extern unsigned char data_020e5934[];
extern void func_020ba1bc(void *);

void *func_020b9d1c(void *obj)
{
    func_020ba1cc(obj);
    *(void **) obj = (void *) data_020e5934;
    func_020ba108((void *) ((char *) obj + 0x10));
    return obj;
}

UnkStruct_020b9cfc *func_020b9cfc(UnkStruct_020b9cfc *self)
{
    func_020ba1cc((void *) ((unsigned int *) self));
    self->vtable = ((int *) data_020e5934);
    func_020ba108(self->sub);
    return self;
}

void func_020b9ce4(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_020ba1bc(r4);
    r4 = (char *) r4 + 0x10;
    func_020ba108(r4);
}
