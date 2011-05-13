/*
 * ConfigTranslatorTest.cpp
 *
 *  Created on: 29 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "ConfigTranslatorTest.h"
#include "config/ConfigTranslator.h"

namespace cryomesh {

namespace config {

void ConfigTranslatorTest::runSuite() {
	cute::suite s;
	s.push_back(CUTE(ConfigTranslatorTest::testRead));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "ConfigTranslatorTest");
}

void ConfigTranslatorTest::testRead() {
	const std::string CONFIG_FILE = "Data/test.config";
	ConfigTranslator trans(CONFIG_FILE);
	const std::list<ConfigEntry> & entry_map = trans.getEntries();
	std::cout << "ConfigTranslatorTest::testRead: " << "" << std::endl;
	std::cout << trans << std::endl;
	ASSERT_EQUAL(3, entry_map.size());

	// option 1
	{
		const ConfigEntry entry = trans.getConfigEntryByCommand("command-1");
		ASSERT_EQUAL(1, entry.getOptions().size());

	}
	// option 2
	{
		const ConfigEntry entry = trans.getConfigEntryByCommand("command-2");
		ASSERT_EQUAL(2, entry.getOptions().size());

	}
	// option 3
	{
		const ConfigEntry entry = trans.getConfigEntryByCommand("command-3");
		ASSERT_EQUAL(3, entry.getOptions().size());

	}
	// option null
	{
			const ConfigEntry entry = trans.getConfigEntryByCommand("commasdasdsad-3");
			ASSERT_EQUAL(0, entry.getOptions().size());

		}
}

}//NAMESPACE

}//NAMESPACE
