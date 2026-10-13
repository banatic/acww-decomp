/* func_020707b8 @ 0x020707b8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
} UnkStruct_020707b8;

extern int data_020e1784;
extern void func_020a887c(void *);

void *func_020707b8(void *obj)
{
    UnkStruct_020707b8 *o;
    o = (UnkStruct_020707b8 *) obj;
    o->unk_00 = (void *) &data_020e1784;
    func_020a887c(obj);
    return obj;
}
