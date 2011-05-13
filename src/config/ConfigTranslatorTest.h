/*
 * ConfigTranslatorTest.h
 *
 *  Created on: 29 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef CONFIGTRANSLATORTEST_H_
#define CONFIGTRANSLATORTEST_H_

#include "ICuteSuite.h"
namespace cryomesh {

namespace config {

class ConfigTranslatorTest : public ICuteSuite {
public:
	ConfigTranslatorTest(){}
	virtual ~ConfigTranslatorTest(){}
	static void runSuite();
	static void testRead();
};

}

}

#endif /* CONFIGTRANSLATORTEST_H_ */
