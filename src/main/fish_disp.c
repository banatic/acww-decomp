/* fish_disp: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204fcf0 @ 0x0204fcf0, 0x4c bytes, Thumb
 * func_0204fcac @ 0x0204fcac, 0x44 bytes, Thumb
 */

typedef struct {
    char c;
} SubObject;

typedef struct {
    void *vtable;
    char pad_04[0x4c];     // 0x04 to 0x50
    char elems[0x16c * 4]; // 0x50 to 0x600
    SubObject sub;         // offset 0x600
} UnkStruct_0204fcf0;

extern void func_0209d2b4(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_02050704(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020dce48[];

void *func_0204fcf0(UnkStruct_0204fcf0 *p)
{
    p->vtable = (void *) ((char *) data_020dce48);
    func_0209d2b4(&p->sub);
    __cxa_vec_cleanup((void *) (p->elems), 4, 0x16c, (((void (*)(void *)) func_02050704)));
    p->vtable = (void *) ((char *) data_020da13c);
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}

void *func_0204fcac(void *obj)
{
    *(unsigned int *) obj = (unsigned int) data_020dce48;
    func_0209d2b4((char *) obj + 0x600);
    __cxa_vec_cleanup((void *) ((char *) obj + 0x50), 4, 0x16c, (((void (*)(void *)) func_02050704)));
    *(unsigned int *) obj = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}
