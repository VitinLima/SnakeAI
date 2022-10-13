/* 
 * File:   serialCommunication.h
 * Author: 160047412
 *
 * Created on 10 de Outubro de 2022, 19:26
 */

#ifndef SERIALCOMMUNICATION_H
#define	SERIALCOMMUNICATION_H

#ifdef	__cplusplus
extern "C" {
#endif

    void print(uint8_t b);
    void printString(const char *str);
    void printFloat(float f);
    void startMessage();
    void endMessage();

#ifdef	__cplusplus
}
#endif

#endif	/* SERIALCOMMUNICATION_H */

