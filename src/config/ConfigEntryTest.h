/*
 * ConfigEntryTest.h
 *
 *  Created on: 29 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef CONFIGENTRYTEST_H_
#define CONFIGENTRYTEST_H_

#include "ICuteSuite.h"

namespace cryomesh {

namespace config {

class ConfigEntryTest :public ICuteSuite {
public:
	ConfigEntryTest(){}
	virtual ~ConfigEntryTest(){}
	static void runSuite();

	static void testParseEntry();
	static void testGetIntegerFormattedOptions();
	static void testToIntegerMultipleValues();
	static void testTokenizeMultipleValueString();
};

}

}

#endif /* CONFIGENTRYTEST_H_ */
