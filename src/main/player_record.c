/* player_record: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02098a18 @ 0x02098a18, 0xc bytes, Thumb
 * func_02098a0c @ 0x02098a0c, 0xc bytes, Thumb
 * func_020989e0 @ 0x020989e0, 0x2c bytes, Thumb
 * func_020989b4 @ 0x020989b4, 0x2c bytes, Thumb
 * func_0209898c @ 0x0209898c, 0x28 bytes, Thumb
 * func_0209895c @ 0x0209895c, 0x30 bytes, Thumb
 * func_02098930 @ 0x02098930, 0x2c bytes, Thumb
 */

struct Entry {
    char data[0xa04];
};

typedef struct {
    char data[0xb4];
} UnkStruct_0209898c;

typedef struct {
    char data[0x0a04];
} UnkStruct_02098930;

extern int func_0209985c(int);
extern int func_020a1368(void);
extern struct Entry data_021ef8ec[4];
extern UnkStruct_0209898c data_021f2fa8[4];
extern int func_0209805c(const unsigned char *ptr);
extern void func_02098050(UnkStruct_02098930 *ptr, unsigned int value);

int func_02098a18(int a)
{
    return a + 0x1d3c;
}

int func_02098a0c(int r0)
{
    return r0 + 0x243e;
}

int func_020989e0(int object)
{
    int n;
    int x;
    n = func_0209985c(object);
    if (n >= 0 && n < 4 && (x = func_020a1368()) != 0) {
        return x + 0x3200 * n;
    }
    return 0;
}

void *func_020989b4(int object)
{
    int idx = func_0209985c(object);
    if (idx >= 0 && idx < 4) {
        return &data_021ef8ec[idx];
    }
    return 0;
}

UnkStruct_0209898c *func_0209898c(int object)
{
    int idx = func_0209985c(object);
    if (idx >= 0 && idx < 4) {
        return &data_021f2fa8[idx];
    }
    return 0;
}

int func_0209895c(int object)
{
    int idx;

    idx = func_0209985c(object);
    if (idx >= 0 && idx < 4) {
        return func_0209805c(((unsigned char *) data_021ef8ec) + idx * 0x0a04);
    } else {
        return 0;
    }
}

void func_02098930(int a, int b)
{
    int idx = func_0209985c(a);
    if (idx >= 0 && idx < 4) {
        func_02098050(&((UnkStruct_02098930 *) data_021ef8ec)[idx], b);
    }
}
