/*
 * ��Ȩ���� (c) [2024-09-27] [By:Codeant]
 *
 * https://discord.gg/Zg5t4Gc7wr
 *
 * ��Դ��������������
 *
 * 1. �������ԡ���״���ṩ�������κ���ʾ��ʾ�ĵ����������������ڶ������ԡ��������ض���;������Ȩ�ĵ�����
 *    The code is provided "as is," without warranty of any kind, express or implied,
 *    including but not limited to the warranties of merchantability, fitness for a
 *    particular purpose, and non-infringement.
 *
 * 2. ���κ�����£����߻��Ȩ�����߾�������ʹ�ñ�������������κ����⡢�𺦻��������θ����������ں�ͬ���ϡ�
 *    ��Ȩ��Ϊ�����������²��������Ρ�
 *    In no event shall the author or copyright holders be liable for any claim,
 *    damages, or other liability, whether in an action of contract, tort, or otherwise,
 *    arising from, out of, or in connection with the software or the use or other
 *    dealings in the software.
 *
 * 3. �û�Ӧ���ге�ʹ�ñ�����ķ��գ����߲��е���ʹ�û��޷�ʹ�ñ�������������κ�ֱ�ӡ���ӡ����⡢żȻ��
 *    ������𺦡�
 *    Users shall assume all risks associated with using the code. The author is not
 *    liable for any direct, indirect, special, incidental, or consequential damages
 *    arising from the use or inability to use the code.
 *
 * 4. ��������ܻ������������Դ��������û����ӣ�ʹ����Щ��������������������Ե����Э�顣
 *    This code may contain references or links to third-party open-source code, which
 *    must be used in accordance with their respective license agreements.
 *
 * 5. ʹ�ñ����뼴��ʾ��ͬ�Ȿ�����������������
 *    By using this code, you agree to all the terms outlined in this disclaimer.
 *
 */

#pragma once
#define _WIN32_WINNT 0x0601
#include "auth.hpp"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>  
#include <stdio.h>
#include <fstream>
#include <tchar.h>

const std::string compilation_date = __DATE__;
const std::string compilation_time = __TIME__;

// Get the current path
std::string GetCurrentPath()
{
	TCHAR szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // Remove the file name, keeping only the directory path
	std::string path = szFilePath;  // For example, path == e:\program\Debug\

	return path;
}

int main()
{
	std::string consoleTitle = "Loader - Built at:  " + compilation_date + " " + compilation_time;
	SetConsoleTitleA(consoleTitle.c_str());

	std::cout << "Connecting.." << std::endl;

	std::ostringstream ss;

	ss << GetCurrentPath() << "Universal-ImGui-D11-Hook.dll";

	std::cout << Codeant::InjectDriverModule("Grand Theft Auto V",ss.str().c_str()) << std::endl;

	std::cout << system("pause") << std::endl;

	return false;
}