/* func_02053010 @ 0x02053010, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x48];
} Struct0x48;

extern Struct0x48 data_021c89fc[];
extern Struct0x48 data_021c884c[];

void func_02053088(Struct0x48 *p);
void func_02053050(void);

void func_02053010(void)
{
    unsigned i;

    for (i = 0; i < 8; i++) {
        func_02053088(&data_021c89fc[i]);
    }

    for (i = 0; i < 6; i++) {
        func_02053088(&data_021c884c[i]);
    }

    func_02053050();
}
