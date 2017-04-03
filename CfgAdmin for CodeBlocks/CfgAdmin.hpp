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

	public: // Propiedades publicas.

	private: // Propiedades privadas.
		bool configState;
		char path[255];

	public: // Metodos publicos
		char* getPath(void);
		bool setPath(const char* path);
		bool setConfigState(bool state);


		int getIntCfg(const char* param);
		char* getStrCfg(const char* param);
		float getFltCfg(const char* param);
		bool getState(void);

		bool setIntCfg(char* paramToSet, const char* value);
		bool setFltCfg(char* paramToSet, const char* value);
		bool setStrCfg(char *paramToSet, const char* value);

		char* getLineWhere(char* param);
		long int getValuePos(char* param);

		bool setIntCfg(char* param, int value);
		bool setStrCfg(char* param, char* value);
		bool setFltCfg(char* param, float value);

	private: // Metodos privados.
		char* getValue(char* param);
		bool verifyLine(char* param, char* bufferObtainedLine);
		char* getLineValue(char* bufferObtainedLine, int paramLen);


	};

}

