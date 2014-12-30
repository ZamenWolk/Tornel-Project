#ifndef  DEFINE_HPP
#define DEFINE_HPP

#ifdef SERVER
#define SOFT "Server"
#else
#define SOFT "Client"
#endif

#define OLD_EXPERIENCE_TO_LEVEL ExponentialFunction(true, 0.9996, 11485.0, 100.0, 0.0, 4000.0)
#define EXPERIENCE_TO_LEVEL ExponentialFunction(true, 0.99996, 114900.0, 100.1, 0.0, 40000.0)
#define STRENGTH_TO_ATTACK_FACTOR ThirdPowerFunction(1, 0.00275, -0.000000625)
#define STRENGTH_TO_STAMINA ThirdPowerFunction(0, 0.1, -0.000011)
#define WISDOM_TO_ATTACK_FACTOR ThirdPowerFunction(1, 0.00275, -0.000000625)
#define WISDOM_TO_MANA ThirdPowerFunction(0, 0.4, -0.0001)
#define TOUGHNESS_TO_ATTACK_REDUCTION ThirdPowerFunction(1, -0.0009, 0.000000225)
#define TOUGHNESS_TO_LIFE ThirdPowerFunction(0, 8.0/30.0, -2.0/30000.0, 0, 2000)
#define MENTAL_RESISTANCE_TO_ATTACK_REDUCTION ThirdPowerFunction(1, -0.0009, 0.000000225)
#define MENTAL_RESISTANCE_TO_LIFE ThirdPowerFunction(0, 4.0/30.0, -1.0/30000.0, 0, 2000)

#endif