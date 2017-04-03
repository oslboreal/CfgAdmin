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

	int Cfg::CfgAdmin::getIntCfg(const char * param)
	{
		int iReturn = 0;
		if (this->getState())
		{
			if (param != NULL)
			{
				iReturn = atoi(getLineWhere((char*)param));
			}

		}
		return iReturn;
	}

	float Cfg::CfgAdmin::getFltCfg(const char * param)
	{
		float fReturn = 0;
		if (this->getState())
		{
			if (param != NULL)
			{
				fReturn = (float)atof(getLineWhere((char*)param));
			}

		}
		return fReturn;
	}

	char * Cfg::CfgAdmin::getStrCfg(const char * param)
	{
		char* bReturn = NULL;
		if (param != NULL)
		{
			bReturn = getLineWhere((char*)param);
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
			char paramToSearch[255];
			strncpy(paramToSearch, param, 255); // Copiamos el contenido.
			strncat(paramToSearch, "=", 255); // Agregamos el igual al final del parámetro.

			if (this->getState()) // Si se construyó correctamente, es decir se corroboro que file exist.
			{
				cReturn = getValue(paramToSearch); // Obtenemos e valor del parámetro.
			}
		}

		return cReturn;
	}

	char * Cfg::CfgAdmin::getValue(char * param)
	{
		char* cReturn = NULL;
		std::fstream CfgFile(this->getPath(), std::fstream::in);
		if (CfgFile.is_open())
		{
			char bufferLine[255];
			int paramLen = strlen(param);
			while (!CfgFile.eof())
			{
				CfgFile.getline(bufferLine, 255);

				if (verifyLine(param, bufferLine))
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
			cReturn = new char[255];
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
