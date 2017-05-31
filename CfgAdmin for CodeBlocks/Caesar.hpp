
/**
 *  Caesar based Encryption Library
 *  Created by: jmv1994
 *  30/05/2017 - 11:54 p.m.
 *
 *
 */

    #include <iostream>
    #include <string.h>
    using namespace std;
    class sCrypt{

    sCrypt()
    {

    }

    public:
    static char* encrypt(const char *str)
    {
        char *cRet;
        if(str != NULL)
        {
            int strTama = strlen(str);
            cRet = new char[strTama]; // Create buffer in memory.

            // Algoritmo.
            int i = 0;
            for(i = 0; i < strTama; i++)
            {
                if(str[i] != '\n')
                {
                    cRet[i] = str[i] + 27;
                }
            }
        }
        return cRet;
    }

    static char* decrypt(const char *str)
    {
         char *cRet;
        if(str != NULL)
        {
            int strTama = strlen(str);
            cRet = new char[strTama]; // Create buffer in memory.

            // Algoritmo.
            int i = 0;
            for(i = 0; i < strTama; i++)
            {
                if(str[i] != '\n')
                {
                    cRet[i] = str[i] - 27;
                }
            }
        }
        return cRet;
    }

    };
