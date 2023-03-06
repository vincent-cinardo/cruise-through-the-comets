#include "MathHelper.h"

float MathHelper::Random(float min, float max)
{
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_real_distribution<float> dist(min, max);
    return dist(engine);
}

int MathHelper::Random(int min, int max)
{
    std::random_device rd;
    std::mt19937 engine{ rd() };
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}
