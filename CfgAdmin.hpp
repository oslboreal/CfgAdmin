#pragma once

#include <fstream> // Include File stream std lib.
#include <string.h>
#include <iostream>

namespace cfg{
	class CfgAdmin
	{
	public:
		CfgAdmin(char* path);
		~CfgAdmin();
	
	public: // Propiedades publicas.

	private: // Propiedades privadas.
		bool configState;
		char path[255];

	public: // Metodos publicos
		char* getPath(void);
		bool setPath(char* path);
		int getIntCfg(char* param);
		char* getStrCfg(char* param);
		float getFltCfg(char* param);
		bool getState(void);

		char* getLineWhere(char* param);

		bool setIntCfg(char* param, int value);
		bool setStrCfg(char* param, char* value);
		bool setFltCfg(char* param, float value);

	private: // Metodos privados.
		char* getValue(char* param);
		bool verifyLine(char* param, char* bufferObtainedLine);
		char* getLineValue(char* bufferObtainedLine, int paramLen);
		
	};

}

