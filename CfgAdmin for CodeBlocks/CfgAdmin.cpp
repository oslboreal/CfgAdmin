#include "CfgAdmin.hpp"

	cfg::CfgAdmin::CfgAdmin(char * path)
	{
		if (!path)
		{
			this->configState = false;
		}
			else
			{
				strncpy(this->path, path, 254); // Si Path no es nulo almacenamos el mismo.
				this->configState = false; // Por defecto el estado inicia en Cero.
				std::fstream cfgFile;
				cfgFile.open(path, std::fstream::in | std::fstream::out);

				if (cfgFile.is_open())
				{
					this->configState = true; // Si logramos abrir el archivo de CFG entonces el estado es abierto.
				}

				if(this->configState) cfgFile.close();
			}
	}

	cfg::CfgAdmin::~CfgAdmin()
	{
	}

	char * cfg::CfgAdmin::getPath(void)
	{
		return this->path;
	}

	bool cfg::CfgAdmin::setPath(char * path)
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

	bool cfg::CfgAdmin::setConfigState(bool state)
	{
		bool bReturn = false;
		if (this->getPath() != NULL) // No podría estár OK sin PATH.
		{
			bReturn = state;
		}
		return bReturn;
	}

	int cfg::CfgAdmin::getIntCfg(char * param)
	{
		int iReturn = 0;
		if (this->getState())
		{
			if (param != NULL)
			{
				iReturn = atoi(getLineWhere(param));
			}

		}
		return iReturn;
	}

	float cfg::CfgAdmin::getFltCfg(char * param)
	{
		float fReturn = 0;
		if (this->getState())
		{
			if (param != NULL)
			{
				fReturn = (float)atof(getLineWhere(param));
			}

		}
		return fReturn;
	}

	char * cfg::CfgAdmin::getStrCfg(char * param)
	{
		char* bReturn = NULL;
		if (param != NULL)
		{
			bReturn = getLineWhere(param);
		}
		return bReturn;
	}

	bool cfg::CfgAdmin::getState(void)
	{
		return this->configState;
	}

	char * cfg::CfgAdmin::getLineWhere(char * param)
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

	char * cfg::CfgAdmin::getValue(char * param)
	{
		char* cReturn = NULL;
		std::fstream cfgFile(this->getPath(), std::fstream::in);
		if (cfgFile.is_open())
		{
			char bufferLine[255];
			int paramLen = strlen(param);
			while (!cfgFile.eof())
			{
				cfgFile.getline(bufferLine, 255);

				if (verifyLine(param, bufferLine))
				{
					cReturn = getLineValue(bufferLine, paramLen); // Obtenemos el valor de la linea encontrada.
				}
			}
			cfgFile.close();// Cerramos elfichero.
		}
		return cReturn;
	}

	bool cfg::CfgAdmin::verifyLine(char * param, char * bufferObtainedLine)
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

	char * cfg::CfgAdmin::getLineValue(char * bufferObtainedLine, int paramLen)
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

	long int cfg::CfgAdmin::getValuePos(char * param)
	{
		int iReturn = 0;
		if (param != NULL)
		{
			std::fstream cfgFile(this->path, std::fstream::in); // Abrimos el fichero como lectura.
			if (cfgFile.is_open())
			{
				this->setConfigState(true);
				int pos;
				char bufferLine[255];
				int paramLen = strlen(param);

				while (!cfgFile.eof())
				{
					pos = cfgFile.tellg();// Obtenemos la posicion de la linea.
					cfgFile.getline(bufferLine, 255);

					if (verifyLine(param, bufferLine))
					{
						iReturn = pos+paramLen+1;
					}
				}
				cfgFile.close();// Cerramos elfichero.

			}
		}
		return iReturn;
	}
