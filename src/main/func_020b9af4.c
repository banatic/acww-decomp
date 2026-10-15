/* func_020b9af4 @ 0x020b9af4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtable;
    char pad_04[0x20];
    char sub;
} UnkStruct_020b9af4;

extern void *func_020b9d1c(void *);
extern void func_020ba108(void *);

extern unsigned char data_020e5944[];

void *func_020b9af4(void *this)
{
    func_020b9d1c(this);
    ((UnkStruct_020b9af4 *) this)->vtable = (void *) data_020e5944;
    func_020ba108(&((UnkStruct_020b9af4 *) this)->sub);
    return this;
}
