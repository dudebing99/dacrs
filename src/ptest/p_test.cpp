// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#define BOOST_TEST_MODULE Process Test Suite

#include "main.h"
#include "txdb.h"
#include "ui_interface.h"
#include "util.h"
#include <string>

#include "./wallet/wallet.h"

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include "chainparams.h"
using namespace std;

//extern void noui_connect();

struct TestingSetup {
	TestingSetup() {
		bool bSetDataDir(false);
		for (int i = 1; i < boost::unit_test::framework::master_test_suite().argc; ++i) {
			string strArgv = boost::unit_test::framework::master_test_suite().argv[i];
			if (string::npos != strArgv.find("-datadir=")) {
				const char* newArgv[] = { boost::unit_test::framework::master_test_suite().argv[0], strArgv.c_str() };
				CBaseParams::IntialParams(2, newArgv);
				bSetDataDir = true;
				break;
			}
		}
		if (!bSetDataDir) {
			int argc = 2;
			char findchar;
#ifdef WIN32
			findchar = '\\';
#else
			findchar = '/';
#endif

			string strCurDir = boost::filesystem::initial_path<boost::filesystem::path>().string();
			int nIndex = strCurDir.find_last_of(findchar);
			int nCount = 3;
			while (nCount--) {
				nIndex = strCurDir.find_last_of(findchar);
				strCurDir = strCurDir.substr(0, nIndex);

			}
#ifdef WIN32
			strCurDir += "\\dacrs_test";
			string strParam = "-datadir=";
			strParam += strCurDir;
			const char* argv[] = { "D:\\cppwork\\soypay\\src\\dacrs-d.exe", strParam.c_str() };
#else
			strCurDir +="/dacrs_test";
			string strParam = "-datadir=";
			strParam +=strCurDir;
			const char* argv[] = {"D:\\cppwork\\soypay\\src\\dacrs-d.exe", strParam.c_str()};
#endif
			CBaseParams::IntialParams(argc, argv);
		}
	}
	~TestingSetup() {
	}
};

BOOST_GLOBAL_FIXTURE(TestingSetup);
