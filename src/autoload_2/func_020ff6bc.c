/* func_020ff6bc @ 0x020ff6bc, 0x84 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int arr[3];
    short s;
} UnkStruct_020ff6bc;

void func_020ff6bc(UnkStruct_020ff6bc *p0, int *p1, int *p2, void *emitter)
{
    p2[0] += p0->s * (p0->arr[0] - p1[2] - p1[5]) >> 12;
    p2[1] += p0->s * (p0->arr[1] - p1[3] - p1[6]) >> 12;
    p2[2] += p0->s * (p0->arr[2] - p1[4] - p1[7]) >> 12;
}
