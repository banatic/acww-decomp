/* func_0200c904 @ 0x0200c904, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/QueueEntry.h"

struct UnkStruct_0200c904 {
    int data[5];
};

extern "C" void func_0200c94c(UnkStruct_0200c904 *s, int a, int b, int c);
extern "C" int func_0200e894(int a, QueueEntry *s);

extern "C" int func_0200c904(int p0, int p1, int p2, int p3, int p4, short p5)
{
    QueueEntry local1;
    func_0200e92c(&local1);
    func_0200e90c(&local1, 7, p4, p5);
    UnkStruct_0200c904 local2;
    func_0200c94c(&local2, p1, p2, p3);
    int result = func_0200e894(p0, &local1);
    func_0200e91c(&local1);
    return result;
}
