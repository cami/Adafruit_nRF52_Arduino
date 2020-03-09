#pragma once

#ifdef NECTIS_DEBUG

#define NECTIS_DEBUG_PRINT(str)     NectisDebug::Print(str)
#define NECTIS_DEBUG_PRINTLN(str)   NectisDebug::Println(str)

class NectisDebug
{
public:
    static void Print(const char* str);
    static void Println(const char* str);

};

#else

#define NECTIS_DEBUG_PRINT(str)
#define NECTIS_DEBUG_PRINTLN(str)

#endif  // NECTIS_DEBUG
