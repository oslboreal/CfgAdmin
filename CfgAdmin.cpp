#include "CfgAdmin.hpp"


	cfg::CfgAdmin::CfgAdmin(char * path)
	{
		if (!path)
		{
			this->configState = false;
		}
			else
			{
				strncpy_s(this->path, path, 254); // Si Path no es nulo almacenamos el mismo.
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
				strncpy_s(this->path,path, 255); // Copy the new path.
				temp.close(); // Close the file.
				bRet = true;
			}
		}
		return bRet;
	}

	int cfg::CfgAdmin::getIntCfg(char * param)
	{
		return 0;
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
			strncpy_s(paramToSearch, param, 255); // Copiamos el contenido.
			strncat_s(paramToSearch, "=", 255); // Agregamos el igual al final del parámetro.
			
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
			int lineLen = strlen(bufferObtainedLine);
			cReturn = new char[255];
			int i = paramLen;
			bool parar = false;
			while (!parar)
			{
				cReturn[i-paramLen] = bufferObtainedLine[i];
				
				if (bufferObtainedLine[i] == NULL)
				{
					parar = true;
				}
				i++;
			}
		}
		return cReturn;
	}
