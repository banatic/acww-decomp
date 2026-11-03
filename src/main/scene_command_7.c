/* scene_command_7: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020155cc @ 0x020155cc, 0xc bytes, Thumb
 * func_020155b4 @ 0x020155b4, 0x16 bytes, Thumb
 * func_02015590 @ 0x02015590, 0x24 bytes, Thumb
 * func_02015578 @ 0x02015578, 0x18 bytes, Thumb
 * func_02015564 @ 0x02015564, 0x14 bytes, Thumb
 */

extern int func_0201596c(int a, int b);

int func_020155cc(int arg)
{
    return func_0201596c(arg, 1);
}

void *func_020155b4(void *r0)
{
    int r2;
    void *r1;

    r2 = 0;
    r1 = *(void **) ((char *) r0 + 0x40);
    if (r1 != 0) {
        if (*(int *) ((char *) r1 + 4) == 5) {
            r2 = 1;
            *(int *) ((char *) r1 + 8) = r2;
        }
    }
    return (void *) r2;
}

int func_02015590(int param1, int param2)
{
    int result;
    int *ptr;

    if (func_0201596c(param1, 2) != 0) {
        ptr = (int *) (param1 + 0xa8);
        *ptr = param2;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_02015578(char *p)
{
    unsigned int *r2;
    r2 = *(unsigned int **) (p + 0x40);
    if (r2 != 0) {
        *(unsigned int *) ((char *) r2 + 0x14) = *(unsigned int *) (p + 0xa8);
        *(p + 0xac) = 1;
    }
    return 0;
}

int func_02015564(void *param)
{
    int result;
    unsigned int *ptr;
    int val;

    result = 0;
    ptr = *(unsigned int **) ((char *) param + 0x40);
    if (ptr != 0) {
        val = *(int *) ((char *) ptr + 4);
        if (val == 5) {
            result = 1;
        }
    }
    return result;
}
