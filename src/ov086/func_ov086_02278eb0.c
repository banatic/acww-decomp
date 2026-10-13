/* func_ov086_02278eb0 @ 0x02278eb0, 0x18 bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov086_022792fc;
extern void func_0202eb20(void *);

typedef struct {
    void *unk_00;
} UnkStruct_02278eb0;

void *func_ov086_02278eb0(void *obj)
{
    ((UnkStruct_02278eb0 *) obj)->unk_00 = (void *) &data_ov086_022792fc;
    func_0202eb20(obj);
    return obj;
}
