#ifndef MAIN_NAND_H_
#define MAIN_NAND_H_

void nandGpioInit(void);
unsigned char nandReadId(void);
unsigned char nandReadStatus(void);

#endif /* MAIN_NAND_H_ */
