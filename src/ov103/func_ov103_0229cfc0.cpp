/* func_ov103_0229cfc0 @ 0x0229cfc0, 0x3c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov103/Obj_ov103_0229e2e0.h"

extern "C" {
void func_ov103_0229ca48(void *);
void func_ov103_0229cbac(void *, unsigned char);
void func_ov002_02207fc0(void *);
void func_ov002_02208098(void *, int);
}

extern "C" void func_ov103_0229cfc0(void *p)
{
    ((unsigned char *) p)[0x2da2] = 0x15;
    ((Obj_ov103_0229e2e0 *) p)->func_ov103_0229c868();
    func_ov002_02207fc0(p);
    func_ov103_0229ca48(p);
    func_ov002_02208098(p, 5);
    func_ov103_0229cbac(p, ((unsigned char *) p)[0x2da4]);
}
