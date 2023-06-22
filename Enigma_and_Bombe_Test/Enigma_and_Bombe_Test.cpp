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
		Rotor rotor1;
		TEST_METHOD(TestNotch)
		{
			Assert::AreEqual(rotor1.getNotch(), 0);
		}

		TEST_METHOD(TestNotch2)
		{
			Rotor rotor2(5, &rotor1);
			Assert::AreEqual(rotor2.getNotch(), 5);


		}
		//TEST_METHOD(TestReference)
		//{
		//	Rotor rotor3(5, &rotor1);
		//	Assert::AreSame(rotor3.getReference(), &rotor1);
		//}

		TEST_METHOD(TestPosition)
		{
			Assert::AreEqual(rotor1.getPosition(), 0);
		}

		TEST_METHOD(TestGetScramblePos)
		{
			Assert::AreEqual(rotor1.getScramblePos(0), 20);
		}

		TEST_METHOD(TestRotate)
		{
			rotor1.rotate();
			Assert::AreEqual(rotor1.getPosition(), 1);
		}

		TEST_METHOD(TestGetScramblePosAfterRotate)
		{
			Assert::AreEqual(rotor1.getScramblePos(0), 13);
		}

	};
	TEST_CLASS(Reflector_test)
	{
	public:
		// Unit Tests for Reflector
		TEST_METHOD(ReflectTest)
		{
			Reflector r1;
			int reflect_Value = r1.reflect(3);
			Assert::AreEqual(reflect_Value, 13);
		}

		TEST_METHOD(Testmethod2)
		{

		}

		TEST_METHOD(Testmethod3)
		{

		}
	};

	TEST_CLASS(Plugboard_test)
	{
	public:
		// Unit Tests for Plugboard
		TEST_METHOD(PlugSwitchTest)
		{
			Plugboard p1;
			int test_connections[26] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
			Assert::AreEqual((p1.PlugSwitch(6)), test_connections[6]);
		}

		TEST_METHOD(SetPlugPositionTest)
		{
			// int PlugPos[10][2] = { {16, 3}, {9, 4}, {11, 15}, {17, 2}, {5, 24 }, { 8, 20}, {7, 22}, {6, 1}, {14, 23}, {18, 25 } };
			Plugboard p1;
			int test_swap[26] = { 0, 6, 17, 16, 9, 24, 1, 22, 20, 4, 10, 15, 12, 13, 23, 11, 3, 2, 25, 19, 8, 21, 7, 14, 5, 18 };
			//					 0  1  2   3   4  5   6   7   8  9  10  11  12  13  14  15  16 17 18  19 20  21  22 23 24  25 
			Assert::AreEqual((p1.test_setPlugPos(test_swap)), 1);
		}

		TEST_METHOD(CreatePlugboardTest)
		{
			Plugboard p1;
			char PlugLet_test[10][2] = {
				{'B','A'},
				{'D','C'},
				{'F','E'},
				{'H','G'},
				{'J','I'},
				{'L','K'},
				{'N','M'},
				{'P','O'},
				{'R','Q'},
				{'T','S'},
			};

			int PlugPos_test[10][2] = {
				{1,0},
				{3,2},
				{5,4},
				{7,6},
				{9,8},
				{11,10},
				{13,12},
				{15,14},
				{17,16},
				{19,18},
			};

			Assert::AreEqual((p1.test_createPlugboard(PlugPos_test, PlugLet_test)), 1);

		}
	};
}
