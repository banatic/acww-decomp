/* func_020b1954 @ 0x020b1954, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtable;
} UnkStruct_020b1954;

extern void *func_020a8cac(UnkStruct_020b1954 *p);
extern void func_020a8c1c(UnkStruct_020b1954 *p);
extern int data_020e4290;

UnkStruct_020b1954 *func_020b1954(UnkStruct_020b1954 *p)
{
    func_020a8cac(p);
    p->vtable = &data_020e4290;
    func_020a8c1c(p);
    return p;
}
