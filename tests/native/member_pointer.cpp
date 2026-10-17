/* Standalone checks for the ROM encoding, independent of a saved game. */
#include "native_member.h"

struct Object {
    unsigned int *vtable;
    int value;
};
typedef NativeMember<Object, int, int> Member;
static_assert(sizeof(Member) == 8, "two ARM words");
static_assert(__builtin_offsetof(Member, adjustment) == 4, "adjustment is second");
static_assert(__is_trivially_copyable(Member), "ABI passes raw words");

static int call(Object *self, int argument)
{
    return self->value + argument;
}

extern "C" int main()
{
    unsigned int vtable[3] = {0, 0, reinterpret_cast<unsigned int>(&call)};
    Object objects[3] = {{vtable, 10}, {vtable, 20}, {vtable, 30}};
    Member direct = {reinterpret_cast<unsigned int>(&call), 0};
    if ((objects->*direct)(7) != 17) return 1;
    // Signed adjustments are bytes, encoded doubled. Use two directions.
    Member positive = {direct.function, 16};
    Member negative = {direct.function, -16};
    if ((objects->*positive)(7) != 27) return 2;
    if (((objects + 1)->*negative)(7) != 17) return 3;
    // Offset 8 is the third vtable slot; virtual flag lives in adjustment.
    Member virt = {8, 17};
    if ((objects->*virt)(7) != 27) return 4;
    virt.adjustment = -15;
    if (((objects + 1)->*virt)(7) != 17) return 5;
    Member nil = {0, 0};
    if (nil) return 6;
    if (nil != 0 || !(nil == nullptr) || direct == 0) return 10;
    // These audited call sites check the function word, even with a virtual flag.
    nil.adjustment = 1;
    if (nil) return 7;
    Member thumb = {0x02262a95, -16};
    Member copied = thumb;
    auto bound = copied.bind(objects + 1);
    if (bound.function != 0x02262a95 || bound.object != objects) return 8;
    if (copied.function != thumb.function || copied.adjustment != -16) return 9;
    return 0;
}
