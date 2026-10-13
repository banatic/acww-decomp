/* func_02052a3c @ 0x02052a3c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 a : 4;
    u32 b : 4;
    u32 s : 16;
} Fields;

extern void func_02052118(int a0, int a1, int a2, unsigned short *a3, unsigned char a4);

void func_02052a3c(int p0, Fields *src)
{
    unsigned short s;
    s = src->s;
    func_02052118(p0, src->a, src->b, &s, 0);
}
