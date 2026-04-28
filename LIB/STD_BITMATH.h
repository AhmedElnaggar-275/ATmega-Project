#ifndef STD_BITMATH_H_
#define STD_BITMATH_H_

//define macros for bit manipulation
#define setBit(reg,bit) (reg |= (1<<bit)) 
#define clearBit(reg,bit) (reg &= ~(1<<bit))
#define toggleBit(reg,bit) (reg ^=(1<<bit))
#define readBit(reg,bit) ((reg & (1<<bit)))

#endif /* STD_BITMATH_H_ */