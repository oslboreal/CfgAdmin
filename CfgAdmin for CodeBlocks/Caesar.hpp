
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
            int i;
            int strTama = strlen(str);
            cRet = new char[strTama + 1]; // Create buffer in memory.
            for(i=0; i < strTama; i++)
            {
                if(i != strTama -1)
                {
                   cRet[i] = 255;
                } else
                {
                    cRet[i] = 0;
                }
            }
            if(cRet != NULL)
            // Algoritmo.
            for(i = 0; i < strTama; i++)
            {
                    cRet[i] = str[i] + 3 * 7;
                    if(i==strTama - 1)
                    {
                        cRet[i + 1] = 0;
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
            int i;
            int strTama = strlen(str);
            cRet = new char[strTama + 1]; // Create buffer in memory.
            for(i=0; i < strTama; i++)
            {
                if(i != strTama -1)
                {
                   cRet[i] = 255;
                } else
                {
                    cRet[i] = 0;
                }
            }
            if(cRet != NULL)
            // Algoritmo.
            for(i = 0; i < strTama; i++)
            {
                    cRet[i] = str[i] - 3 * 7;
                    if(i==strTama - 1)
                    {
                        cRet[i + 1] = 0;
                    }
            }
        }
        return cRet;
    }

    };
