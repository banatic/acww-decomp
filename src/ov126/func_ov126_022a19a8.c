/* func_ov126_022a19a8 @ 0x022a19a8, 0x2e bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

struct Obj_ov126_022a20c8;
extern int func_ov002_02207f48(struct Obj_ov126_022a20c8 *, int);
extern void func_ov002_022080a0(struct Obj_ov126_022a20c8 *, int);
extern void func_ov126_022a0be0(struct Obj_ov126_022a20c8 *);
extern void func_ov126_022a0934(struct Obj_ov126_022a20c8 *);
extern void func_ov126_022a16ac(struct Obj_ov126_022a20c8 *);

void func_ov126_022a19a8(struct Obj_ov126_022a20c8 *obj)
{
    if (func_ov002_02207f48(obj, 0) != 0) {
        func_ov002_022080a0(obj, 2);
        func_ov126_022a0be0(obj);
        func_ov126_022a0934(obj);
    }
    func_ov126_022a16ac(obj);
}
