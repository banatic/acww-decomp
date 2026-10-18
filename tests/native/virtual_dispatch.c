/* The first call changes the vtable; the actual shop copy must read it afterward. */
#include <stdint.h>

_Static_assert(sizeof(void *) == 4, "Native fixture requires 32-bit pointers");
extern void func_ov100_0229e3b0(void *);
typedef void (*Callback)(void *);
static uint32_t actors[2][0x2278 / 4];
static void *current;
static int stage, failed, selected, observed;

static void wrong_slot(void *self)
{
    (void) self;
    failed = 1;
}

static void observe(void *self, int value)
{
    if (stage != 1 || self != (char *) current + 0x2274) {
        failed = 2;
    }
    stage = 2;
    observed = value;
}

static void first_target(void *self)
{
    observe(self, 17);
}
static void second_target(void *self)
{
    observe(self, 29);
}
static Callback before[4] = {wrong_slot, wrong_slot, wrong_slot, wrong_slot};
static Callback after[2][4] = {
    {wrong_slot, wrong_slot, wrong_slot, first_target},
    {wrong_slot, wrong_slot, wrong_slot, second_target},
};

void func_ov100_0229e374(void *self)
{
    if (stage != 0 || self != current) {
        failed = 3;
    }
    *(Callback **) ((char *) self + 0x2274) = after[selected];
    stage = 1;
}

int main(void)
{
    for (selected = 0; selected < 2; selected++) {
        current = actors[selected];
        stage = observed = 0;
        *(Callback **) ((char *) current + 0x2274) = before;
        func_ov100_0229e3b0(current);
        if (stage != 2 || observed != (selected ? 29 : 17)) {
            return 4;
        }
        if (failed) {
            return failed;
        }
    }
    return 0;
}
