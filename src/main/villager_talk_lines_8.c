/* villager_talk_lines_8: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201fc54 @ 0x0201fc54, 0x8 bytes, Thumb
 * func_0201fc4c @ 0x0201fc4c, 0x8 bytes, Thumb
 * func_0201fc14 @ 0x0201fc14, 0x38 bytes, Thumb
 */

extern void func_0202a5e8(void *, void *);
extern void func_02020360(void *);

void func_0201fc54(void *argument0, void *argument1)
{
    func_0202a5e8((void *) argument0, (void *) argument1);
}

void func_0201fc4c(void *argument0)
{
    func_02020360((void *) argument0);
}

int func_0201fc14(int x)
{
    switch (x) {
        case 6:
        case 9:
        case 12:
        case 15:
            return 6;
        case 8:
        case 11:
        case 14:
        case 17:
            return 12;
        default:
            return 9;
    }
}
