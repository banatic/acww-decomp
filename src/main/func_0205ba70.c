/* func_0205ba70 @ 0x0205ba70, 0x3c bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern int MATH_CountPopulation(int);

int func_0205ba70(int *arr)
{
    int sum = 0;
    unsigned offset;
    for (offset = 0; offset < 0xde; offset += 4) {
        sum += MATH_CountPopulation(*(int *) ((char *) arr + offset));
    }
    return sum * 7777;
}
