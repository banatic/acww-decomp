/* func_020b3550 @ 0x020b3550, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e50dc;
extern void func_020b373c(void *ptr);

typedef struct {
    void *vtable;
    int pad_04;
    char sub[1];
} UnkStruct_020b3550;

UnkStruct_020b3550 *func_020b3550(UnkStruct_020b3550 *this)
{
    this->vtable = &data_020e50dc;
    func_020b373c(this->sub);
    return this;
}
