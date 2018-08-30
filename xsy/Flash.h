
#ifndef __DMA_H
#define __DMA_H

#define InfoA   (0x1080)    //��Ϣ�洢�� InfoA
#define InfoB   (0x1000)    //��Ϣ�洢�� InfoB

void FlashInit();
void FlashErase(unsigned int Addr);
void FlashWriteChar (unsigned int addr,char Data);
char FlashReadChar (unsigned int Addr);
void FlashWriteWord(unsigned int addr,unsigned int Data);
unsigned int FlashReadWord(unsigned int Addr);

void Yaw_SAV();

#endif /* __DMA_H */
