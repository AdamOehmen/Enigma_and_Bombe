#include "pch.h"
#include "CppUnitTest.h"
#include "../Enigma_and_Bombe/Driver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
/*
* Example Test Method:
	TEST_METHOD(TestClassInit)
	{
		std::string name = "Bill";
		MyClass mc(name);
		Assert::AreEqual(name, mc.GetName());
	}
*/
namespace EnigmaandBombeTest
{
	TEST_CLASS(EnigmaandBombeTest)
	{
	public:
		// Unit Tests for Rotors
		TEST_METHOD(Testmethod1)
		{
			Rotor rotor1;
			//Rotor rotor2(1, &rotor1 );
			Assert::AreEqual(rotor1.getNotch(), 0);
			//Assert::AreEqual(rotor2.getNotch(), 1);
		}
		// Unit Tests for Reflector
		TEST_METHOD(Testmethod2)
		{
		}
		// Unit Tests for Plugboard
		TEST_METHOD(Testmethod3)
		{
		}
	};
}
