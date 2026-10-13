/* func_02094f44 @ 0x02094f44, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02094f44 UnkStruct_02094f44;
struct UnkStruct_02094f44 {
    void *vtable;
};

extern char data_020e2f54[];
extern void func_020a887c(void *p);
extern __arm void func_020edb3c(void *p);

UnkStruct_02094f44 *func_02094f44(UnkStruct_02094f44 *p)
{
    p->vtable = data_020e2f54;
    func_020a887c(p);
    func_020edb3c(p);
    return p;
}
