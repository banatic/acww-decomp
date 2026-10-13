/* func_0204fcf0 @ 0x0204fcf0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dce48;
extern char data_020da13c;
extern void func_0209d2b4(void *);
extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_02050704(void);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);

typedef struct {
    char c;
} SubObject;

typedef struct {
    void *vtable;
    char pad_04[0x4c];     // 0x04 to 0x50
    char elems[0x16c * 4]; // 0x50 to 0x600
    SubObject sub;         // offset 0x600
} UnkStruct_0204fcf0;

void *func_0204fcf0(UnkStruct_0204fcf0 *p)
{
    p->vtable = (void *) &data_020dce48;
    func_0209d2b4(&p->sub);
    func_02138c48(p->elems, 4, 0x16c, func_02050704);
    p->vtable = (void *) &data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
