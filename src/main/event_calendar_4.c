/* event_calendar_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204019c @ 0x0204019c, 0x1a bytes, Thumb
 * func_02040180 @ 0x02040180, 0x1a bytes, Thumb
 */

typedef struct {
    int c;
} UnkStruct_0204019c;

typedef struct {
    int c;
} UnkStruct_02040180;

extern int func_020401b8(int a, int b, UnkStruct_0204019c cc, int d);

int func_0204019c(int a, int b, UnkStruct_0204019c cc, int d)
{
    int value;

    volatile int result[2];
    value = func_020401b8(a, b, cc, d);
    result[0] = value;
    return value;
}

int func_02040180(int a, int b, UnkStruct_02040180 cc, int d)
{
    int value;

    volatile int result[2];
    value = func_020401b8(a, b, *(UnkStruct_0204019c *) &cc, d);
    result[0] = value;
    return value;
}
