/* func_ov002_022087bc @ 0x022087bc, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208844(void *p);
extern int data_ov002_0220baf4;

void *func_ov002_022087bc(void *p)
{
    *(int **) p = &data_ov002_0220baf4;
    func_ov002_02208844(p);
    return p;
}
