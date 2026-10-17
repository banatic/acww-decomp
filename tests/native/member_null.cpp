/* Link the five actual PC copies against a two-word ROM null object. */
unsigned int __ptmf_null[2] = {0, 0};

extern "C" {
void func_ov046_02261590(void *);
void func_ov051_02260f94(void *);
void func_ov070_0227986c(void *);
void func_ov073_02278f98(void *);
void func_ov076_02278fa8(void *);
}

static void callback(void *object)
{
    ++*static_cast<unsigned int *>(object);
}

int main()
{
    struct Case { void (*run)(void *); unsigned int offset; } cases[] = {
        {func_ov046_02261590, 0xb8}, {func_ov051_02260f94, 0xb4},
        {func_ov070_0227986c, 0xb8}, {func_ov073_02278f98, 0xb8},
        {func_ov076_02278fa8, 0xbc},
    };
    static_assert(sizeof(void *) == 4, "32-bit game boundary");
    for (const Case &test : cases) {
        unsigned int object[0xc8 / 4] = {};
        unsigned int *member = object + test.offset / 4;
        member[0] = reinterpret_cast<unsigned int>(&callback);
        member[1] = 0;
        test.run(object);
        if (object[0] != 1 || member[0] != 0 || member[1] != 0) return 1;
        // The ROM tests the callable word; a null's adjustment is not decoded.
        member[1] = 0xfffffff8u;
        test.run(object);
        if (object[0] != 1 || member[0] != 0 || member[1] != 0xfffffff8u) return 2;
        for (unsigned int i = 1; i < sizeof(object) / sizeof(object[0]); ++i) {
            if (i != test.offset / 4 + 1 && object[i] != 0) return 3;
        }
    }
    return 0;
}
