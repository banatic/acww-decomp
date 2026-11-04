/* process_8: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020eea3c @ 0x020eea3c, 0x10 bytes, ARM
 * func_020ee9a0 @ 0x020ee9a0, 0x9c bytes, ARM
 * func_020ee964 @ 0x020ee964, 0x3c bytes, ARM
 */

extern unsigned int data_02138fbc[];
extern int data_0213e7fc;
extern int data_021fd034;
extern int data_021fd014;
extern int data_021fd004;
extern int data_021fd024;
extern int data_021fcff8;
extern int func_020ee834(int *arg);
extern int func_020eea4c(int *arg);

unsigned int func_020eea3c(unsigned int arg0)
{
    return data_02138fbc[arg0];
}

void func_020ee9a0(void)
{
    data_0213e7fc = 4;
    func_020ee834(&data_021fd034);
    data_0213e7fc = 2;
    func_020ee834(&data_021fd014);
    data_0213e7fc = 3;
    func_020ee834(&data_021fd004);
    data_0213e7fc = 5;
    func_020ee834(&data_021fd024);
    data_0213e7fc = 1;
    func_020eea4c(&data_021fcff8);
    data_0213e7fc = 0;
}

void func_020ee964(void)
{
    data_0213e7fc = 5;
    func_020ee834(&data_021fd024);
    data_0213e7fc = 0;
}
