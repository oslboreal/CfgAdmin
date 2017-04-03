#pragma once

#include <fstream> // Include File stream std lib.
#include <string.h>
#include <stdlib.h>
#include <iostream>

namespace Cfg{
	class CfgAdmin
	{
	public:
		CfgAdmin(const char* path);
		~CfgAdmin();

	private: // Propiedades privadas.
		bool configState;
		char path[255];
		char* getPath(void);
        bool setPath(const char* path);
        bool setConfigState(bool state);
        char* getLineWhere(char* param);
		long int getValuePos(char* param);
		char* getValue(char* param);
		bool verifyLine(char* param, char* bufferObtainedLine);
		char* getLineValue(char* bufferObtainedLine, int paramLen);

	public: // Metodos publicos
        char* getValue(const char* param);
		bool getState(void);
		bool setValue(char *paramToSet, const char* value);
	};

}

