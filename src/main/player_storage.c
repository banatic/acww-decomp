/* player_storage: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203a690 @ 0x0203a690, 0x2 bytes, Thumb
 * func_0203a68c @ 0x0203a68c, 0x2 bytes, Thumb
 * func_0203a678 @ 0x0203a678, 0x14 bytes, Thumb
 * func_0203a674 @ 0x0203a674, 0x2 bytes, Thumb
 */

void func_0203a690(void *object) {}

void func_0203a68c(void *object) {}

void func_0203a678(unsigned short *arr)
{
    int i;
    for (i = 0; i < 90; i++) {
        arr[i] = 0xfff1;
    }
}

unsigned short *func_0203a674(void *record)
{
    return (unsigned short *) record;
}
