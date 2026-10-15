/* func_ov003_0221617c @ 0x0221617c, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_02073908(int, int);
extern int func_0203e1c4(void);
extern int func_ov003_02216124(void *, int, int);
extern int data_020ccf94;

void func_ov003_0221617c(void *self)
{
    if (*(signed short *) ((char *) self + 0x8e) != 0) {
        return;
    }
    if (func_02056f94((char *) self + 0x2d0) == 0) {
        return;
    }
    if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0 && func_0203e1c4() == 0) {
        return;
    }
    func_ov003_02216124(self, 6, -1);
}
