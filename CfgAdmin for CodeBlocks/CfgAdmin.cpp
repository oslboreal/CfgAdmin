#include "CfgAdmin.hpp"

	Cfg::CfgAdmin::CfgAdmin(const char* path)
	{
		if (!path)
		{
			this->configState = false;
		}
			else
			{
				strncpy(this->path, path, 254); // Si Path no es nulo almacenamos el mismo.
				this->configState = false; // Por defecto el estado inicia en Cero.
				std::fstream CfgFile;
				CfgFile.open(path, std::fstream::in | std::fstream::out);

				if (CfgFile.is_open())
				{
					this->configState = true; // Si logramos abrir el archivo de Cfg entonces el estado es abierto.
				}

				if(this->configState) CfgFile.close();
			}
	}

	Cfg::CfgAdmin::CfgAdmin(const char* path, bool encryption)
	{
		if (!path) // If is null set config state.
		{
			this->configState = false;
		}
			else
			{
				strncpy(this->path, path, 254); // Si Path no es nulo almacenamos el mismo.
				this->configState = false; // Por defecto el estado inicia en Cero.
				std::fstream CfgFile;
				CfgFile.open(path, std::fstream::in | std::fstream::out);

				if (CfgFile.is_open())
				{
					this->configState = true; // Si logramos abrir el archivo de Cfg entonces el estado es abierto.
				}

				if(this->configState) CfgFile.close();
			}
	}

	Cfg::CfgAdmin::~CfgAdmin()
	{
	}

	char * Cfg::CfgAdmin::getPath(void)
	{
		return this->path;
	}

	bool Cfg::CfgAdmin::setPath(const char* path)
	{
		bool bRet = false;
		if (getState() && path != NULL)
		{
			std::fstream temp(path, std::fstream::in);
			if (temp.is_open())
			{
				strncpy(this->path,path, 255); // Copy the new path.
				temp.close(); // Close the file.
				bRet = true;
			}
		}
		return bRet;
	}

	bool Cfg::CfgAdmin::setConfigState(bool state)
	{
		bool bReturn = false;
		if (this->getPath() != NULL) // No podría estár OK sin PATH.
		{
			bReturn = state;
		}
		return bReturn;
	}

	char * Cfg::CfgAdmin::getValue(const char * param)
	{
		char* bReturn = NULL;
		if (param != NULL)
		{
			bReturn = getLineWhere((char*)param); // En caso de que el parámetro sea válido obtenemos la linea.
		}
		return bReturn;
	}

	bool Cfg::CfgAdmin::getState(void)
	{
		return this->configState;
	}

	char * Cfg::CfgAdmin::getLineWhere(char * param)
	{
		char* cReturn = NULL;
		if (param != NULL)
		{
			char paramToSearch[255]; // Creamos un buffer.
			strncpy(paramToSearch, param, 255); // Copiamos el contenido.
			strncat(paramToSearch, "=", 255); // Agregamos el igual al final del parámetro.

			if (this->getState()) // Si se construyó correctamente, es decir se corroboro que file exist.
			{
				cReturn = internalGetValue(paramToSearch); // Obtenemos e valor del parámetro.
			}
		}

		return cReturn;
	}

	char * Cfg::CfgAdmin::internalGetValue(char * param)
	{
		char* cReturn = NULL;
		std::fstream CfgFile(this->getPath(), std::fstream::in); // Abrimos el archivo como lectura.
		if (CfgFile.is_open())
		{
			char bufferLine[1024];
			int paramLen = strlen(param);
			while (!CfgFile.eof())
			{
				CfgFile.getline(bufferLine, 1024); // Obtenemos la linea.
				if (verifyLine(param, bufferLine)) // Si es la linea.
				{
					cReturn = getLineValue(bufferLine, paramLen); // Obtenemos el valor de la linea encontrada.
				}
			}
			CfgFile.close();// Cerramos elfichero.
		}
		return cReturn;
	}

	bool Cfg::CfgAdmin::verifyLine(char * param, char * bufferObtainedLine)
	{
		int i, paramLen, cont=0;
		paramLen = strlen(param);
		bool bReturn = false;
		if (param != NULL && bufferObtainedLine != NULL)
		{
			for (i = 0; i <= paramLen - 1; i++)
			{
				if (bufferObtainedLine[i] == param[i])
				{
					cont++;
				}
				if (cont == paramLen)
				{
					bReturn = true;
				}
			}
		}
		return bReturn;
	}

	char * Cfg::CfgAdmin::getLineValue(char * bufferObtainedLine, int paramLen)
	{
		char* cReturn = NULL;
		if (bufferObtainedLine != NULL)
		{
			cReturn = new char[255]; // Generamos espacio en memoria para retornar el valor.
			int i = paramLen;
			bool parar = false;
			while (!parar)
			{
				cReturn[i-paramLen] = bufferObtainedLine[i];
				if (bufferObtainedLine[i] == 0)
				{
					parar = true;
				}
				i++;
			}
		}
		return cReturn;
	}

	long int Cfg::CfgAdmin::getValuePos(char * param)
	{
		int iReturn = 0;
		if (param != NULL)
		{
			std::fstream CfgFile(this->path, std::fstream::in); // Abrimos el fichero como lectura.
			if (CfgFile.is_open())
			{
				this->setConfigState(true);
				int pos;
				char bufferLine[255];
				int paramLen = strlen(param);
				while (!CfgFile.eof())
				{
					pos = CfgFile.tellg();// Obtenemos la posicion de la linea.
					CfgFile.getline(bufferLine, 255);
					if (verifyLine(param, bufferLine))
					{
						iReturn = pos+paramLen+1;
					}
				}
				CfgFile.close();// Cerramos elfichero.

			}
		}
		return iReturn;
	}


	bool Cfg::CfgAdmin::getEncryptionMode(void)
	{
	    return this->encryptionMode;
	}

    bool Cfg::CfgAdmin::encrypt(const char * path, const char* outFileName)
    {
        if(path != NULL)
        {
            std::fstream CfgFileToEncrypt(path, std::fstream::in); // Abrimos el archivo como lectura.
            std::fstream CfgFileToSave(outFileName, std::fstream::out); // Abrimos el archivo como escrituera.
            if (CfgFileToEncrypt.is_open())
            {
                char* encryptOut = NULL;
                while (!CfgFileToEncrypt.eof())
                {
                    char bufferLine[1024];
                    CfgFileToEncrypt.getline(bufferLine, 1024); // Obtenemos la linea.
                    cout << "Linea obtenida al momento de encriptar: " << bufferLine << endl;
                    encryptOut = sCrypt::encrypt(bufferLine);
                    cout << "Misma linea encriptada: " << encryptOut << endl;
                    CfgFileToSave << encryptOut << '\n';
                }
            }
            CfgFileToEncrypt.close();
            CfgFileToSave.close();
        }
        return false;
    }

    bool Cfg::CfgAdmin::decrypt(const char * path, const char* outFileName)
    {

        if(path != NULL)
        {
            std::fstream CfgFileToDecyrpt(path, std::fstream::in); // Abrimos el archivo como lectura.
            std::fstream CfgFileToSave(outFileName, std::fstream::out); // Abrimos el archivo como escritura.
            if (CfgFileToDecyrpt.is_open())
            {
                char* encryptOut = NULL;
                while (!CfgFileToDecyrpt.eof())
                {
                    char bufferLine[2048];
                    CfgFileToDecyrpt.getline(bufferLine, 2048); // Obtenemos la linea.

                   cout << "Linea obtenida al momento de encriptar: " << bufferLine << endl;
                    encryptOut = sCrypt::decrypt(bufferLine);
                    cout << "Misma linea encriptada: " << encryptOut << endl;
                    CfgFileToSave << encryptOut << '\n';

                }
            }
            CfgFileToDecyrpt.close();
            CfgFileToSave.close();
        }
        return false;
    }



