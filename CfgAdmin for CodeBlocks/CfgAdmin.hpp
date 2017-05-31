#pragma once

#include <fstream> // Include File stream std lib.
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <Caesar.hpp>


namespace Cfg{
	class CfgAdmin
	{
	public:
		CfgAdmin(const char* path);
		CfgAdmin(const char* path, bool encryption);
		~CfgAdmin();

	private: // Propiedades privadas.
		bool configState;
		bool encryptionMode;
		char path[255];
		char* getPath(void);
        bool setPath(const char* path);
        bool setConfigState(bool state);
        char* getLineWhere(char* param);
		long int getValuePos(char* param);
		char* internalGetValue(char* param);
		bool verifyLine(char* param, char* bufferObtainedLine);
		char* getLineValue(char* bufferObtainedLine, int paramLen);

	public: // Metodos publicos
        char* getValue(const char* param);
		bool getState(void);
		bool getEncryptionMode(void);
		bool setValue(char *paramToSet, const char* value);
		static bool encrypt(const char* path, const char* outFileName);
        static bool decrypt(const char* path, const char* outFileName);

	};

}

