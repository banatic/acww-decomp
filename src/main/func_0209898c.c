/* func_0209898c @ 0x0209898c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209985c(int);

typedef struct {
    char data[0xb4];
} UnkStruct_0209898c;

extern UnkStruct_0209898c data_021f2fa8[4];

UnkStruct_0209898c *func_0209898c(int object)
{
    int idx = func_0209985c(object);
    if (idx >= 0 && idx < 4) {
        return &data_021f2fa8[idx];
    }
    return 0;
}
