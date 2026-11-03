/* effect_system_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02090360 @ 0x02090360, 0xa bytes, Thumb
 * func_0209035c @ 0x0209035c, 0x2 bytes, Thumb
 * func_0209033c @ 0x0209033c, 0x1e bytes, Thumb
 * func_0209031c @ 0x0209031c, 0x1e bytes, Thumb
 * func_020902f8 @ 0x020902f8, 0x22 bytes, Thumb
 * func_020902d0 @ 0x020902d0, 0x28 bytes, Thumb
 */

void func_02090360(int *p)
{
    p[0] = -1;
    p[1] = 0;
}

void func_0209035c(void *object) {}

void func_0209033c(char *p)
{
    int i;
    for (i = 0; i < 10; i++) {
        func_02090360((int *) p);
        p += 8;
    }
}

void func_0209031c(unsigned char *p)
{
    int i;

    for (i = 0; i < 10; i++) {
        func_0209035c(p);
        p += 8;
    }
}

int func_020902f8(int *p, int key)
{
    int i, result;
    result = 0;
    i = result;
    while (i < 10) {
        if (key == p[0]) {
            result = p[1];
            break;
        }
        p += 2;
        i++;
    }
    return result;
}

int func_020902d0(int *arr, int v1, int v2)
{
    int i, found;
    found = 0;
    i = found;
    while (i < 10) {
        if (*arr == ~found) {
            *arr = v1;
            arr[1] = v2;
            found = 1;
            break;
        }
        arr += 2;
        i++;
    }
    return found;
}
