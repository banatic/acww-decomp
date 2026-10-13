/* func_020b0518 @ 0x020b0518, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
} Func020b0518Elem;

void func_020b0518(Func020b0518Elem *array)
{
    unsigned int i = 0;
    do {
        array[i].a = 0;
        array[i].b = 0;
        array[i].c = 0;
        array[i].d = 0x800;
        i++;
    } while (i < 2);
}
